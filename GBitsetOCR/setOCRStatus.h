-(char)setOCRStatus:(char *)name{
char OCRStatus=0;
//value OCR status for grammar recognition //0 - not set 1-vowel 3 - root letter 4 -  root letter with vowel 5 - letter 6 -  sanskrit letter 7- sanskrit vowel 8- letter with sanskrit vowel 9- mark 10- space 

//name=name;
m=0;

while(m<1){  //one iteration loop
//cout<<"name[0]="<<name[0]<<" record_="<<record_<<endl;

/////////////////////////////////punctuation mark
if ((name[0]=='/'||name[0]=='!'||name[0]==';'||name[0]=='#'||name[0]=='@'||name[0]=='=')&&name[1]==0)
{OCRStatus=9;break;} // 2- mark 
if ((name[0]=='@'&&name[1]=='#')&&name[2]==0){OCRStatus=9;break;} // 2- mark 
if (name[0]=='_'||name[0]==' '){OCRStatus=10;break;} // 2- space 


////////////////////////////////Vowel
if((name[0]=='e'||name[0]=='i'||name[0]=='u'||name[0]=='o')&&name[1]==0)
{OCRStatus=1;break;}  // 5 - letter
if((name[0]=='A'||name[0]=='E'||name[0]=='I'||name[0]=='U'||name[0]=='O')&&name[1]==0)
{OCRStatus=7;break;}  // 7- sanskrit vowel


//////////////////////////////letter 
if((name[0]=='\''||name[0]=='g'||name[0]=='d'||name[0]=='b'||name[0]=='m'||
name[0]=='s'||name[0]=='l'||name[0]=='r'||name[0]=='m'||name[0]=='n'||name[0]=='a')&&name[1]==0)
{OCRStatus=5;break;}  // 5 - letter
if(name[0]=='n'&&name[1]=='g'&&name[2]==0)
{OCRStatus=5;break;}  // 5 - letter


//////////////////////////////root letter
//alphabet
if(name[0]=='k'||name[0]=='c'||name[0]=='j'||name[0]=='t'||name[0]=='p'||name[0]=='w'||name[0]=='z'||name[0]=='y'||name[0]=='h'){ //ka ca ja ta pa wa za ya ha 
	if(name[1]=='a'&&name[2]==0){OCRStatus=3;break;}  // 5 - root letter
	if(name[1]=='y'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter yatag
	if(name[1]=='r'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter ratag
	if(name[1]=='l'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter latag
	if(name[1]=='w'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter wasur
}	

if(name[0]=='n'||name[1]=='g'||name[0]=='b'||name[0]=='m'||name[0]=='l'||name[0]=='g'){ 
	if(name[1]=='y'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter yatag
	if(name[1]=='r'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter ratag
	if(name[1]=='l'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter latag
	if(name[1]=='w'&&name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter wasur
}	


if((name[0]=='k'||name[0]=='z'||name[0]=='s'||name[0]=='c'||name[0]=='p'||name[0]=='t')&&name[1]=='h'){ //kha zha sha cha pha tha 
	if(name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter
	if(name[2]=='y'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter yatag
	if(name[2]=='r'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter ratag
	if(name[2]=='l'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter latag
	if(name[2]=='w'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter wasur
}

if(name[0]=='t'&&name[1]=='s'){ //tsa
	if(name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter
	if(name[2]=='y'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter yatag
	if(name[2]=='r'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter ratag
	if(name[2]=='l'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter latag
	if(name[2]=='w'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter wasur
}


if(name[0]=='t'&&name[1]=='s'&&name[2]=='h'){ //tsha
	if(name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter
	if(name[3]=='w'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter wasur
}

if(name[0]=='d'&&name[1]=='z'){ //dza
	if(name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter
	if(name[2]=='y'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter yatag
	if(name[2]=='r'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter ratag
	if(name[2]=='l'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter latag
	if(name[2]=='w'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter wasur
}

if(name[0]=='n'&&name[1]=='y'){ //nya
	if(name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter
	if(name[2]=='w'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter wasur
}

//////////////////// ra la sa upstring
if (name[0]=='r'||name[0]=='l'||name[0]=='s'){

		if(name[1]=='k'||name[1]=='c'||name[1]=='j'||name[1]=='t'||name[1]=='p'||name[1]=='z'||name[1]=='h'||name[1]=='n'||name[1]=='g'||
		name[1]=='b'||name[1]=='m'||name[1]=='l'||name[1]=='d'){ 
			if(name[2]=='a'&&name[3]==0){OCRStatus=3;break;}  // 5 - root letter
			if(name[2]=='y'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter yatag
			if(name[2]=='r'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter ratag
			if(name[2]=='l'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter latag
			if(name[2]=='w'&&name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter wasur
		}	

		if((name[1]=='k'||name[1]=='z'||name[1]=='s'||name[1]=='c'||name[1]=='p'||name[1]=='t')&&name[2]=='h'){ //kha zha sha cha pha tha 
			if(name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter
			if(name[3]=='y'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter yatag
			if(name[3]=='r'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter ratag
			if(name[3]=='l'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter latag
			if(name[3]=='w'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter wasur
		}

		if(name[1]=='t'&&name[2]=='s'){ //tsa
			if(name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter
			if(name[3]=='y'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter yatag
			if(name[3]=='r'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter ratag
			if(name[3]=='l'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter latag
			if(name[3]=='w'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter wasur
		}

		if(name[1]=='d'&&name[2]=='z'){ //dza
			if(name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter
			if(name[3]=='y'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter yatag
			if(name[3]=='r'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter ratag
			if(name[3]=='l'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter latag
			if(name[3]=='w'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter wasur
		}

		if(name[1]=='n'&&name[2]=='g'){ //nga
			if(name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter
			if(name[3]=='y'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter yatag
			if(name[3]=='r'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter ratag
			if(name[3]=='l'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter latag
			if(name[3]=='w'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter wasur
		}

		if(name[1]=='n'&&name[2]=='y'){ //nya
			if(name[3]=='a'&&name[4]==0){OCRStatus=3;break;}  // 5 - root letter
			if(name[3]=='w'&&name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter wasur
		}

		if(name[1]=='t'&&name[2]=='s'&&name[2]=='h'){ //tsha
			if(name[4]=='a'&&name[5]==0){OCRStatus=3;break;}  // 5 - root letter
			if(name[4]=='w'&&name[5]=='a'&&name[6]==0){OCRStatus=3;break;}  // 5 - root letter wasur
		}



}////////////////////// ra la sa upstring  if (name[0]=='r'||name[0]=='l'||name[0]=='s'){

i=0;
		while(name[i]!=0){
		if(name[i]=='e'||name[i]=='i'||name[i]=='u'||name[i]=='o'){
		{OCRStatus=4;break;}  //4 -  root letter with vovel
		}
		if(name[i]=='A'||name[i]=='I'||name[i]=='U'||name[i]=='O'||name[1]=='E')
		{OCRStatus=8;break;}  //8 -  root letter with vovel
		i++;}

i=0;
		while(name[i]!=0){
		if(name[i]=='+'){OCRStatus=6;break;}  //6 -  sanskrit letter
		i++;}
	
m++;}	

return OCRStatus;	
	
}///////////////////////////////////////////////////////////////////////////









