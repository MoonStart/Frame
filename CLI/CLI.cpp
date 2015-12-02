#include <iostream>
#include <sstream>
#include <string>
#include <fstream> 
#include <algorithm>
#include <vector>
#include <map>
using namespace std;


#define TYPE_INT         "INT"
#define TYPE_ENUM        "ENUM"
#define TYPE_STRING      "STRING"
#define TYPE_CMD         "cmd"
#define SPACE            0x20
#define SEMI             0x3B

/* INT=[1-36] if INT=null which mean no range */
string format_int_parameter(string str, stringstream& rule, int paranum)
{
  string::iterator it;
  int min_pos = 0;
  int max_pos = 0;
  int spe_pos = 0;
  int pos = 0;

  transform(str.begin(), str.end(), str.begin(), toupper);
  
  if(str.find(TYPE_INT) == str.npos)
  	return "";
  /* output the str as commont */
  rule <<endl<<endl<<endl;
  rule <<"/* "<<str<<" */"<<endl;

  /* which mean the parameter have no range */
  if(str.find("NULL")==str.npos)
  {
     rule<<"%type para"<<paranum<<"{int}"<<endl<<"para"<<paranum<<"(A) ::= INT(X). {A=aton(X);}"<<endl;
	 return rule.str();
  }
  
  for(it=str.begin(); it!=str.end(); it++)
  {
    if(*it == '[')
    {
      min_pos = pos+1;
	}
	else if(*it == '-')
	{
      spe_pos = pos;
	}
	else if(*it == ']')
	{
      max_pos = pos-1;
	}
	pos ++;
  }
  
  rule<<"%type para"<<paranum<<"{int}"<<endl<<"para"<<paranum<<"(A) ::= INT(X). {A=aton(X); if(A<"<<
  	 str.substr(min_pos, spe_pos-min_pos)<<" || A>"<<
     str.substr(spe_pos+1, max_pos-spe_pos)<<")return OUT_RANGE;}"<<endl;
  return rule.str();
}


/* INT=[1-36] if INT=null which mean no range */
string format_string_parameter(string str, stringstream& rule, int paranum)
{
    return "";
}
/*
str = ENUM=[start|medium|end]
the format should be like this:
"%type para1 {int}
para1(A) ::= ON. {A=1;}
para1(A) ::= OFF. {A=0;}"
*/
string format_enum_parameter(string str, stringstream& rule, int paranum)
{
  string::iterator it;
  int sta_pos = 0;
  int end_pos = 0;
  int spe_pos = 0;
  int pos = 0;
  int num = 0;
  char buffer[100];

  transform(str.begin(), str.end(), str.begin(), toupper);
  /* output the str as commont */
  rule <<endl<<endl<<endl;
  rule <<"/*"<<str<<"*/"<<endl;
  
  rule<<"%type para"<<paranum<<"{int}"<<endl;
  
  if(str.find(TYPE_ENUM) == str.npos)
  	return "";

  for(it=str.begin(); it!=str.end(); it++)
  {
    if(*it == '[')
    {
      sta_pos = pos+1;
	}
	else if(*it == '|')
	{
      spe_pos = pos;
	  string val = str.substr(sta_pos, spe_pos-sta_pos);
	  sprintf_s(buffer,"para%d(A) ::= %s. {A = %d;}\r\n", paranum, val.c_str(), num);
      string temp_str(buffer);
	  rule<<temp_str;
	  sta_pos = spe_pos+1;
	  num++;
	}
	else if(*it == ']')
	{
      end_pos = pos;
	  string val = str.substr(sta_pos, end_pos-sta_pos);
	  sprintf_s(buffer,"para%d(A) ::= %s. {A = %d;}\r\n", paranum, val.c_str(), num);
      string temp_str(buffer);
	  rule<<temp_str;
	}
	pos ++;
  }
  //cout<<rule.str()<<endl;
  return rule.str();
}

string format_funtion_name(vector<string>& nodeArray)
{
   string name;
   vector<string>::iterator it;
   for(it=nodeArray.begin(); it!=nodeArray.end(); it++)
   {
     name += *it;
	 name += "_";
   }
   name += "func";
   transform(name.begin(), name.end(), name.begin(), tolower);
  // cout<<name<<endl;
   return name;
}

string format_function_pramater(vector<string>&nodeArray, vector<pair<string, string>>& paraMap)
{
  string para;
  size_t num =1;

  vector<pair<string, string>>::iterator it = paraMap.begin();
  for(; it != paraMap.end(); it++)
  { 
    para += it->first;
	para += " ";
	para += it->second;
	if(num < paraMap.size())
	{
      para += ", ";
	}
	num++;
  }
  
  transform(para.begin(), para.end(), para.begin(), tolower);
  //cout<<para<<endl;
  return para;
}

#define LIST_ACTION \
        do{\
        nodeArray.pop_back();\
		paramap.push_back(pair<string, string>("int", nodeArray[nodeArray.size()-1]));\
		cmdstr<<"para"<<paranum++<<"("<<paracode<<")";\
		if(*it == SEMI)\
		{\
          cmdstr<<".";\
		}\
		else\
		{\
          cmdstr<<" ";\
		}\
		codeArray.push_back(paracode++);\
        }while(0)
/* cmd ::= ED EDFA POWER para1(A). {ed_edfa_power(A);} */
string format_command_line(string line, fstream& header)
{
  string funname;            /* used to construct the function name lower format */
  string parameter;          /* used to construct the function's parameter */
  stringstream rule;         /* used to construct the every parameter rule */
  vector<char> codeArray;    /* used to insted parameter's value, asm requred */
  stringstream cmdstr;       /* output all cmd string */
  string::iterator it;        
  std::vector<string> nodeArray; /* contain all node for every  command line */
  std::vector<std::pair<string, string>>paramap; /* output to the function file header and cpp */
  std::vector<std::pair<string, string>>::iterator paramapit;
  int pos = 0;
  int npos = 0;
  char paracode='A';
  int  paranum = 1;
	
  transform(line.begin(), line.end(), line.begin(), toupper);

  cmdstr << "cmd ::= ";
 
  for(it=line.begin(); it!=line.end(); it++)
  {
    npos ++;
    if(*it == SPACE || *it == SEMI)
    {
      string node = line.substr(pos, npos-pos-1);
	  nodeArray.push_back(node);

	  if(node.find(TYPE_INT) != node.npos)
	  {
        format_int_parameter(node, rule, paranum);
        LIST_ACTION;
	  }
	  else if(node.find(TYPE_ENUM) != node.npos)
	  {
        format_enum_parameter(node, rule, paranum);
	    LIST_ACTION;
	  }
	  else if(node.find(TYPE_STRING) != node.npos)
	  {
        format_string_parameter(node, rule, paranum);
	    LIST_ACTION;
	  }
	  else 
	  {
	   cmdstr<<node;
	   if(*it == SPACE)
	   {
		cmdstr<<" ";
	   }
	  }
	  pos = npos;
	}
  }
  funname = format_funtion_name(nodeArray);
  parameter = format_function_pramater(nodeArray, paramap);

  /* output the function define,this should be output in file header */
  cout<<"int "<<funname<<"("<<parameter<<");"<<endl;
  cout<<"{"<<endl;
  paramapit = paramap.begin();
  while(paramapit != paramap.end())
  {
    transform(paramapit->second.begin(), paramapit->second.end(), paramapit->second.begin(), tolower);
    cout<<"    cout<<"<<"\""<<paramapit->second<<"\""<<" = <<"<<paramapit->second<<"<<endl;"<<endl;
    paramapit++;
  }
  cout<<"}"<<endl;

  
 {/* output the cmdlist */
  cmdstr<<"{"<<funname<<"(";
  vector<char>::iterator codeit = codeArray.begin();
  size_t num = 1;
  while(codeit != codeArray.end())
  {
    cmdstr<<(*codeit);
	if(num < (codeArray.size()))
	{
      cmdstr<<", ";
	}
	codeit++;
	num ++;
  }
  cmdstr<<")"<<";}"<<rule.str()<<endl;
 }
  cout<<cmdstr.str();
  return "";
}


int main()
{
  string line = "ED EDFA THREASHOLD INT=[1-36] POWER ENUM=[start|medium|end] STATUS ENUM=[on|off];";
  string format; 
  fstream headr;   /* we out put all function define in this file */ 
#if 0
  headr.open("C:\Users\Leslie\Desktop\CLI\func_define.h",ios::in, 0); 
  if(!headr) 
  { 
    cout<<"can't open header file"<<endl; 
    exit(1); 
  } 
#endif
  format_command_line(line, headr);
 return 0;
}