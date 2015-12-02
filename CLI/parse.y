input ::= cmdlist.
cmdlist ::= cmdlist ecmd.
cmdlist ::= ecmd.
ecmd ::= SEMI.
ecmd ::= cmdx SEMI.         
cmdx ::= cmd. { std::cout<<"CLI AGENT"<<endl; }


cmd ::= ED EDFA THREASHOLD para1(A). {ed_edfa_threashold(A);}
%type para1 {int}
para1(A) ::= INT(X). {A=aton(X); range(A);}