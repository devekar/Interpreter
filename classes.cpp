/*
 * classes.cpp
 *
 *  Created on: Oct 13, 2012
 *      Author: vaibhav
 */

#include "classes.h"
using namespace std;

//************************************************************
// to create appropriate indentation during printing of program
int tabs=0;
void indent()
{
	for(int i=0;i<tabs;i++)
		cout<<"\t";
}


//============================================================
Id* Id::eIds[20];
int Id::count=0;

Id::Id(std::string n)
{
	declared=false;
	initialised=false;
	name=n;
	val=GARBAGE;
}

Id* Id::parseId(std::string s)
{
	int i;

	for(i=0;i<count;i++)
		if(eIds[i]->name == s) break;

	if(i==count) {eIds[count++]=new Id(s);}

	return eIds[i];
}

int Id::getIdVal()
{
	if(!declared) {printId();cout<<" not declared";exit(1);}
	else if(val==GARBAGE) {printId();cout<<" not initialised";exit(1);}
	return val;
}

void Id::setIdVal(int i)
{
	if(!declared) {printId();cout<<" not declared";exit(1);}
	val=i;
	initialised=true;
}

void Id::printId()
{
	cout<<name<<" ";
}

void Id::declId()
{
	declared=true;
}


//============================================================
IdList::IdList()
{
	id=0;idl=0;
	t=Tokenizer::instance();ip=InputData::instance();
}

void IdList::parseIdList()
{
	id=Id::parseId(t->get_token());

	t->skip_token();
	if(t->get_token()==",") {
		t->skip_token();  //,
		idl=new IdList();idl->parseIdList();
	}

}

void IdList::printIdList()
{
	id->printId();
	if(idl) {cout<<", ";idl->printIdList();}
}

void IdList::readIdList()
{
	id->setIdVal(ip->get_next_input());
	if(idl) idl->readIdList();
}

void IdList::writeIdList()
{
	int i=id->getIdVal();
	id->printId();
	cout<<"= ";
	cout<<i<<"\n";
	if(idl) idl->writeIdList();
}

void IdList::declIdList()
{
	id->declId();
	if(idl) idl->declIdList();
}


//============================================================
Op::Op()
{
	alt=0;id=0;i=0;exp=0;
	t=Tokenizer::instance();
}

void Op::parseOp()
{
	if(t->get_token_no()==31) {
		alt=1;
		i=atoi(t->get_token().c_str());
		t->skip_token(); //skip the integer
	}
	else if(t->get_token_no()==32) {
		alt=2;
		id=Id::parseId(t->get_token());
		t->skip_token(); //skip the id
	}
	else if(t->get_token()=="(") {
		alt=3;
		t->skip_token(); //(
		exp=new Exp(); exp->parseExp();
		t->skip_token(); //)
	}

}

void Op::printOp()
{
	if(alt==1) cout<<i<<" ";
	else if(alt==2) id->printId();
}

int Op::execOp()
{
	if(alt==1) return i;
	else if(alt==2) return id->getIdVal();
	else return exp->execExp();
}


//============================================================
Fac::Fac()
{
	op=0;f=0;alt=0;
	t=Tokenizer::instance();
}

void Fac::parseFac()
{
	op=new Op(); op->parseOp();
	if(t->get_token()!="*") alt=1;
	else {
		alt=2;
		t->skip_token();   //*
		f=new Fac();f->parseFac();
	}
}

void Fac::printFac()
{
	op->printOp();
	if(alt==1) return;

	cout<<"* ";
	f->printFac();
}

int Fac::execFac()
{
	if(alt==1) return op->execOp();
	else return (op->execOp() * f->execFac());
}


//============================================================
Exp::Exp()
{
	f=0;exp=0;alt=0;
	t=Tokenizer::instance();
}

void Exp::parseExp()
{
	f=new Fac(); f->parseFac();

	if(t->get_token()==";") alt=1;
	else if(t->get_token()=="+") alt=2;
	else alt=3;

	if(alt>1) {t->skip_token();
	exp=new Exp(); exp->parseExp();
	}
}

void Exp::printExp()
{
	f->printFac();
	if(alt==1) return;

	if(alt==2) cout<<"+ ";
	else cout<<"- ";
	exp->printExp();
}

int Exp::execExp()
{
	if(alt==1) return f->execFac();
	else if(alt==2) return (f->execFac() + exp->execExp());
	else return (f->execFac() - exp->execExp());
}


//============================================================
Comp::Comp()
{
	op1=op2=0; alt=0; string cop;
	t=Tokenizer::instance();
}

void Comp::parseComp()
{
	t->skip_token();  //(
	op1=new Op(); op1->parseOp();
	cop=t->get_token();t->skip_token();  // cop
	op2=new Op(); op2->parseOp();
	t->skip_token();  //)

	if(cop=="!=") alt=1;
	else if(cop=="==") alt=2;
	else if(cop=="<") alt=3;
	else if(cop==">") alt=4;
	else if(cop=="<=") alt=5;
	else if(cop==">=") alt=6;
}

void Comp::printComp()
{
	cout<<"( ";
	op1->printOp();
	cout<<" "<<cop<<" ";
	op2->printOp();
	cout<<") ";
}

bool Comp::execComp()
{
	int a=op1->execOp();
	int b=op2->execOp();

	if(alt==1) return (a!=b);
	else if(alt==2) return (a==b);
	else if(alt==3) return (a<b);
	else if(alt==4) return (a>b);
	else if(alt==5) return (a<=b);
	else return (a>=b);
}


//============================================================
Cond::Cond()
{
	cp=0; c1=c2=0; alt=0;
	t=Tokenizer::instance();
}

void Cond::parseCond()
{
	std::string s=t->get_token();
	if(s=="(") {
		alt=1;
		cp=new Comp();cp->parseComp();
	}
	else if(s=="!") {
		alt=2;t->skip_token(); //!
		c1=new Cond();c1->parseCond();
	}
	else if(s=="[") {
		t->skip_token(); //[
		c1=new Cond();c1->parseCond();

		string andor=t->get_token();
		t->skip_token(); // skip && or ||
		c2=new Cond();c2->parseCond();

		if(andor=="&&") alt=3;
		else if(andor=="||") alt=4;
		t->skip_token(); //]
	}

}

void Cond::printCond()
{
	if(alt==1) cp->printComp();
	else if(alt==2) {cout<<"!";c1->printCond();}
	else {
		cout<<"[ ";
		c1->printCond();
		if(alt==3) cout<<"&& ";
		else cout<<"|| ";
		c2->printCond();
		cout<<"] ";
	}
}

bool Cond::execCond()
{
	if(alt==1) return cp->execComp();
	else if(alt==2) return (!c1->execCond());
	else if(alt==3) return (c1->execCond() && c2->execCond());
	else return (c1->execCond() || c2->execCond());
}


//============================================================
Assign::Assign()
{
	id=0; exp=0;
	t=Tokenizer::instance();
}

void Assign::parseAssign()
{
	id=Id::parseId(t->get_token());
	t->skip_token(); //skip id
	if(t->get_token()!="=") {cout<<"Symbol: = expected";exit(1);}
	t->skip_token(); //=
	exp=new Exp(); exp->parseExp();
	t->skip_token(); //;
}

void Assign::printAssign()
{
	indent(); id->printId();
	cout<<"= ";
	exp->printExp();
	cout<<";\n";
}

void Assign::execAssign()
{
	int i=exp->execExp();
	id->setIdVal(i);
}


//============================================================
If::If()
{
	c=0;s1=s2=0;alt=0;
	t=Tokenizer::instance();
}

void If::parseIf()
{
	t->skip_token(); //if
	c=new Cond(); c->parseCond();

	if(t->get_token()!="then") {cout<<"Keyword \'then\' not found";exit(1);}
	t->skip_token(); //then
	s1=new SS(); s1->parseSS();

	if(t->get_token()=="end") {alt=1;}
	else if(t->get_token()=="else"){
		t->skip_token();//else
		s2=new SS(); s2->parseSS();alt=2;
	}
	else {cout<<"\'end\' or \'else\' expected.";exit(1);}
	t->skip_token(); //end
	t->skip_token(); //;
}

void If::printIf()
{
	indent(); cout<<"if ";
	c->printCond();
	cout<<"then\n";
	tabs++;
	s1->printSS();
	tabs--;
	if(alt==2) {
		indent(); cout<<"else\n";
		tabs++; s2->printSS(); tabs--;
	}
	indent(); cout<<"end;\n";
}

void If::execIf()
{
	if(c->execCond()) s1->execSS();
	else if(s2) s2->execSS();
}


//============================================================
Loop::Loop()
{
	c=0;s=0;
	t=Tokenizer::instance();
}

void Loop::parseLoop()
{
	t->skip_token(); //while
	c=new Cond();c->parseCond();

	t->skip_token(); //loop
	s=new SS(); s->parseSS();

	t->skip_token(); //end
	t->skip_token(); //;
}

void Loop::printLoop()
{
	indent(); cout<<"while ";
	c->printCond();
	cout<<"loop\n";
	tabs++;
	s->printSS();
	tabs--;
	indent();cout<<"end;\n";
}

void Loop::execLoop()
{
	while(c->execCond())
		s->execSS();
}


//============================================================
Input::Input()
{
	idl=0;
	t=Tokenizer::instance();
}

void Input::parseInput()
{
	t->skip_token(); //read
	idl=new IdList(); idl->parseIdList();
	t->skip_token(); //;
}

void Input::printInput()
{
	indent();
	cout<<"read ";
	idl->printIdList();
	cout<<";\n";
}

void Input::execInput()
{
	idl->readIdList();
}


//============================================================
Output::Output()
{
	idl=0;
	t=Tokenizer::instance();
}

void Output::parseOutput()
{
	t->skip_token(); //write
	idl=new IdList();
	idl->parseIdList();
	t->skip_token();  //;
}

void Output::printOutput()
{
	indent();
	cout<<"write ";
	idl->printIdList();
	cout<<";\n";
}

void Output::execOutput()
{
	idl->writeIdList();
}


//============================================================
Stmt::Stmt()
{
	alt=0;s1=0;s2=0;s3=0;s4=0;s5=0;
	t=Tokenizer::instance();
}

void Stmt::parseStmt()
{
	int s=t->get_token_no();

	if(s==32) {alt=1; s1=new Assign();s1->parseAssign();}
	else if(s==5) {alt=2; s2=new If();s2->parseIf();}
	else if(s==8) {alt=3;s3=new Loop();s3->parseLoop();}
	else if(s==10) {alt=4;s4=new Input();s4->parseInput();}
	else if(s==11) {alt=5; s5=new Output();s5->parseOutput();}
	else {cout<<"Wrong use of keyword: "<<t->get_token();}
}

void Stmt::printStmt()
{
	if(alt==1) s1->printAssign();
	else if(alt==2) s2->printIf();
	else if(alt==3) s3->printLoop();
	else if(alt==4) s4->printInput();
	else if(alt==5) s5->printOutput();
}

void Stmt::execStmt()
{
	if(alt==1) s1->execAssign();
	else if(alt==2) s2->execIf();
	else if(alt==3) s3->execLoop();
	else if(alt==4) s4->execInput();
	else if(alt==5) s5->execOutput();
}


//============================================================
SS::SS()
{
	s=0;ss=0;t=Tokenizer::instance();
}

void SS::parseSS()
{
	s=new Stmt; s->parseStmt();
	if(t->get_token()!="end"&&t->get_token()!="else") {ss=new SS();ss->parseSS();}
}

void SS::printSS()
{
	s->printStmt();
	if(ss) ss->printSS();
}

void SS::execSS()
{
	s->execStmt();
	if(ss) ss->execSS();
}


//==============================================
Decl::Decl()
{
	idl=0;
	t=Tokenizer::instance();
}

void Decl::parseDecl()
{
	if(t->get_token()!="int") {cout<<"Datatype should be int";exit(1);}
	t->skip_token(); //int
	idl=new IdList;
	idl->parseIdList();
	t->skip_token(); //;
}

void Decl::printDecl()
{
	indent();
	cout<<"int ";
	idl->printIdList();
	cout<<";\n";
}

void Decl::execDecl()
{
	idl->declIdList();
}


//======================================================
DS::DS()
{
	d=0;ds=0;
	t=Tokenizer::instance();
}

void DS::parseDS()
{
	if(t->get_token()=="begin") {cout<<"No declaration found.";exit(1);}
	d=new Decl(); d->parseDecl();
	if(t->get_token()!="begin") {ds=new DS();ds->parseDS();}
}


void DS::printDS()
{
	d->printDecl();
	if(ds) ds->printDS();
}

void DS::execDS()
{
	d->execDecl();
	if(ds) ds->execDS();
}


//============================================================
Prog::Prog()
{
	t=Tokenizer::instance();
	ds=0;ss=0;
}

void Prog::parseProg()
{
	if(t->get_token()!="program") {cout<<"Keyword program not found.";exit(1);}
	t->skip_token(); //program
	ds=new DS(); ds->parseDS();

	if(t->get_token()!="begin") {cout<<"Keyword begin not found";exit(1);}
	t->skip_token(); //begin
	ss=new SS(); ss->parseSS();

	if(t->get_token()!="end") {cout<<"Keyword end not found";exit(1);}
	t->skip_token(); //end
}



void Prog::printProg()
{
	cout<<"\n*********** PROGRAM ***********\n\n";

	cout<<"program\n\n";
	tabs++;
	ds->printDS();

	cout<<"\nbegin\n\n";
	ss->printSS();
	cout<<"\nend";
}

void Prog::execProg()
{
	cout<<"\n\n\n*********** OUTPUT ***********\n\n";
	ds->execDS();
	ss->execSS();
}
