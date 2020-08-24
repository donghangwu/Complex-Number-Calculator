#include <iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<cmath>
#include"complexNumber.h"
#include"memories.h"
using namespace std;

enum commandError{fileNoexist,invalidInput,exits,lowercase};

typedef void (*fFunc)(string,string&,bool&,bool&,vector<string>&);
typedef map<string, fFunc> commandMap;
typedef void (*Func)(string ,string&, vector<string>&,memories&);
typedef map<char, Func> donemap;
typedef void (*Fun)(string ,string&, vector<string>&,bool&,memories);
typedef map<string, Fun> endmap;


void checkInput(string input, bool &done);
void commandline(int argc, const char *argv[], commandMap, donemap , endmap EE);
void performComm(int argc,const char *argv[],string& commandfile,bool&record,bool&exe,memories&values,vector<string>&commands, commandMap table);
void twoinput(bool &exe, string &input, vector<string> &commands);

void help();

void exec(string,string& filename,bool &record, bool &exe, vector<string> &commands);
void recording(string,string& filename, bool &record, bool &exe, vector<string> &commands);
void oneArgv(string filename,memories& values);

void assgin(string ,string& filename,vector<string>& command, memories &values);
void load(string , string& filename, vector<string>& command, memories &values);
void print(string ,string& filename,vector<string>& command, memories &values);
void let(string , string& filename, vector<string>& command, memories &values);
void save(string ,string &filename, vector<string>& command, memories &values);
void Trig(string , string &filename, vector<string>& command, memories &values);
void Mag(string , string &filename, vector<string>& command, memories &values);

void wexit(string input ,string& filename, vector<string>& command,bool&done,memories values);
void exit(string input ,string& filename, vector<string>& command,bool&done,memories values);

void exitsave(bool name,string& filename);

void loadfile(ifstream &in, string filename, memories &values);
complexNumber operation(complexNumber one, complexNumber two, char op);
string extension(string filename, string exten);
void checksavefile(string &filename,string exten);
void readexefile(ifstream &in,vector<string>&command);
void getinput(istream &in, string &input);
void performEXE(string &input,bool &exe,vector<string>&command);
void writeRecord(bool record,string filename,vector<string>& command);
void saveComplex(string filename,memories values);


int main(int argc,const char*argv[])
{
    commandMap table;
    donemap pro;
    endmap EE;
    table["RECORD"]=recording;
    table["EXECUTE"]=exec;
    pro[' ']=pro['=']=assgin;
    pro['O']=load;
    pro['R']=print;
    pro['E']=let;
    pro['A']=save;
    pro['r']=Trig;
    pro['a']=Mag;
    EE["WEXI"]=wexit;
    EE["EXIT"]=exit;
    commandline(argc,argv,table,pro,EE);
    return 0;
}



void checkInput(string input,bool& done)
{
    if(input.empty())
    {
        done = true;
        throw exits;
    }
    string checks[9]={"LET","SAVE","LOAD","PRINT","WEXIT","EXIT","Trig","Mag","="};
    string check2[6]={"let","save","load","print","wexit","exit"};
    bool pp=false;
    bool lower=false;
    for(int i =0; i<9;++i)
    {
        if(input.find(checks[i])!=string::npos)
        {
            pp=true;
        }
    }
    for(int i =0;i<6;++i)
    {
        if(input.find(check2[i])!=string::npos)
        {
            lower=true;
        }
    }
    if(lower)
    {
        throw lowercase;
    }
    if(!pp)
    {
        throw invalidInput;
    }
}
void performComm(int argc, const char *argv[], string& commandfile, bool &record, bool &exe, memories &values, vector<string> &commands, commandMap table)
{
    if(argc>1)
    {
        if(argc==3)
        {
            string com;
            com=argv[1];
            if(com!="EXECUTE" && com!="RECORD")
            {

                cout<<"incorrect commandline argument "<<endl;
                return;
            }
            table[argv[1]](argv[2],commandfile,record,exe,commands);
        }
        else if(argc==2)
        {
            oneArgv(argv[1],values);
        }
        else
        {
            cout<<"there are more than two parameters on the command line"<<endl;
        }
    }
}

void commandline(int argc, const char *argv[], commandMap table,donemap pro,endmap EE)
{
    vector<string> commands,filecommand;
    memories values;
    string filename,input,commandfile;
    bool record=false,exe=false;
    bool done=false;

    performComm(argc,argv,commandfile,record,exe,values,commands,table);
    while(!done)
    {
        twoinput(exe,input,commands);
        if(input.find("WEXIT")!=string::npos||input.find("EXIT")!=string::npos)
        {
            EE[input.substr(0,4)](input,filename,commands,done,values);
        }
        else
        {
            try
            {
                checkInput(input,done);
                pro[input[1]](input,filename,commands,values);
            }
            catch (complexNumberError e)
            {
                switch (e)
                {
                case NoTrig:
                    cout<<"cannot do TRIG version for this complex number "<<endl;
                    break;
                case noARG:
                    cout<<"undefined argument for complex number "<<endl;
                    break;
                default:
                    break;
                }
            }
            catch (ErrorFraction f)
            {
                switch (f) {
                case ZeroDenom:
                    cout<<"cannot have a zero at denominator "<<endl;
                    break;
                default:
                    break;
                }

            }
            catch(commandError c)
            {
                switch (c) {
                case fileNoexist:
                    cout<<"the file does not exist "<<endl;
                    break;
                case invalidInput:
                    cout<<"invalid inputs"<<endl;
                    help();
                    break;
                case exits:
                    break;
                case lowercase:
                    cout<<"please enter all command in UPPER CASE"<<endl;
                    break;
                default:
                    break;
                }
            }
        }
    }
    writeRecord(record,commandfile,commands);
}

void twoinput(bool&exe,string&input,vector<string>&commands)
{
    if(exe)
    {
        performEXE(input,exe,commands);
        cout<<input<<endl;
    }
    else
    {
        cout<<"INPUT: ";
        getinput(cin,input);
        commands.push_back(input);
    }
}

void assgin(string input, string& filename, vector<string> &command, memories &values)
{
    char one,two,op,Left,assig;
    stringstream ss;
    ss<<input;
    ss>>Left;
    ss>>assig;
    ss>>one;
    if(one=='~')
    {
        op='~';
        ss>>two;
        values[Left]=~values[two];

    }
    else
    {
        ss>>op;
        ss>>two;
        values[Left]=operation(values[one],values[two],op);
    }
    cout<<Left<<" = "<<values[Left]<<endl;
}

complexNumber operation(complexNumber one, complexNumber two,char op)
{
    complexNumber result;
    switch (op)
    {
    case '+':
        result=one+two;
        break;
    case '-':
        result=one-two;
        break;
    case '/':
        result = one/two;
        break;
    case '*':
        result = one * two;
        break;
    case '^':
        result = one ^ two;
        break;
    default:
        cout<<"operator "<<op<<" does not support "<<endl;
        break;
    }
    return result;
}
void load(string input,string& filename,vector<string>& command, memories &values)
{
    if(input.size()<=4)
    {
        throw invalidInput;
    }
    string line;
    string file;
    ifstream in;
    line = input.substr(input.find("LOAD")+4,input.length());
    stringstream ss;
    ss<<line;
    ss>>file;
    filename=extension(file,".complex");
    cout<<"loading to:"<<filename<<endl;
    in.open(filename);
    if(in.fail())
    {
        throw fileNoexist;
    }
    else
    {
        loadfile(in,filename,values);
    }


}



void loadfile(ifstream& in,string filename, memories &values)
{
    string line;
    stringstream ss;
    while(!in.eof())
    {
        getinput(in,line);
        ss<<line;
        ss>>values;
        cout<<line<<endl;
        ss=stringstream();
        line=string();

    }

}

void Mag(string input, string &filename, vector<string> &command, memories &values)
{
    string line;
    stringstream ss;
    char name;
    line=input.substr(input.find('(')+1,input.length());
    ss<<line;
    ss>>name;
    cout<<"magnitude of "<<name<<" is: "<<values[name].mag()<<endl;

}
void print(string input, string& filename, vector<string>& command, memories &values)
{
    if(input.size()<=5)
    {
        throw invalidInput;
    }
    string line;
    char printer;
    line = input.substr(input.find("PRINT")+5,input.length());
    stringstream ss;
    ss<<line;
    ss>>printer;
    cout<<printer<<" = "<<values[printer]<<endl;
}
void let(string input,string& filename,vector<string>& command, memories &values)
{
    stringstream ss;
    string line;
    char one,two,three,op,junk;
    if(input.size()<=3)
    {
        throw invalidInput;
    }
    line=input.substr(input.find("LET")+4,input.length());
    ss<<line;
    ss>>one;//F
    ss.putback(one);
    ss>>values;


    cout<<one<<" = "<<values[one]<<endl;

}
void save(string input, string& filename, vector<string>& command, memories &values)
{
    if(input.size()<=4)
    {
        throw invalidInput;
    }
    stringstream ss;
    string line;
    ss<<input;
    input=string();
    while(ss>>line)
    {
        input+=line;
    }
    filename=input.substr(input.find("SAVE")+4,input.length());
    filename=extension(filename,".complex");
    checksavefile(filename,".complex");
    saveComplex(filename,values);

}

void saveComplex(string filename, memories values)
{
    ofstream out;
    out.open(filename);
    for(int i =0; i<26;++i)
    {
        out<<char(i+65)<<" = "<<values[i+65]<<endl;
    }
    out.close();


}

void Trig(string input, string &filename, vector<string> &command, memories &values)
{
    char fun;
    string line;
    line=input.substr(input.find("(")+1,input.length());
    stringstream ss;
    ss<<line;
    ss>>fun;
    cout<<fun<<" = ";
    values[fun].trig();
    cout<<endl;
}

void wexit(string input, string &filename, vector<string> &command, bool &done,memories values)
{
    stringstream ss;
    string line;
    if(input.length()>=6)
    {
        line = input.substr(input.find("WEXIT")+5,input.length());
        ss<<line;
        ss>>line;
        filename=extension(line,".complex");
        checksavefile(filename,".complex");
        saveComplex(filename,values);
        done = true;
    }
    else
    {
        cout<<"The command WEXIT shall  be followed by a filename "<<endl;
    }

}
void exit(string input, string &filename, vector<string> &command, bool &done,memories values)
{
    string line;
    if(command.size()>=2)
    {
        line=command.at(command.size()-2);
    }
    if(line.find("SAVE")==string::npos)
    {
        cout<<"do you wish to save? ";
        getinput(cin,line);
        if(toupper(line[0])=='Y')
        {
            exitsave(false,filename);
            saveComplex(filename,values);
        }

    }
    done = true;
}

void exitsave(bool name,string &filename)
{
    string file;
    if(!name)
    {
        cout<<"plese enter a file name: ";
        getinput(cin,file);
    }
    filename=extension(file,".complex");
    checksavefile(filename,".complex");

}

void oneArgv(string filename, memories &values)
{
    ifstream in;
    if(filename.find("/h")!=string::npos||filename.find("/?")!=string::npos)
    {
        help();
        exit(0);
    }
    else
    {
        filename=extension(filename,".complex");
        cout<<"load "<<filename<<endl;
        in.open(filename);
        if(in.is_open())
        {
            loadfile(in,filename,values);
        }
        else
        {
            cout<<"loading file does not exist "<<endl;
        }

    }
}

void recording(string s,string &filename,bool &record,bool& exe,vector<string>& commands)
{
    record=true;
    filename=extension(s,".spt");
}

void writeRecord(bool record,string filename, vector<string> &command)
{
    ofstream out;
    ifstream in;
    if(record)
    {
        cout<<"record mode is on "<<endl;
        checksavefile(filename,".spt");
        out.open(filename);
        while(command.size()!=0)
        {
            out<<command.front()<<endl;
            command.erase(command.begin());
        }
        out.close();

    }
}

void exec(string s,string &filename,bool &record, bool &exe, vector<string> &commands)
{
    ifstream in;
    exe=true;
    filename=extension(s,".spt");
    in.open(filename);
    if(in.fail())
    {
        exe=false;
        cout<<"EXECUTE spt file "<<filename<<" does not exist "<<endl;
        return;
    }
    readexefile(in,commands);
    in.close();
}

void performEXE(string &input, bool &exe, vector<string> &command)
{
    input=command.front();
    command.erase(command.begin());
    if(command.size()==0)
    {
        exe=false;
    }
}

string extension(string filename,string exten)
{
    string newname;
    if(filename.find(exten)!=string::npos)
    {
        return filename;
    }
    else if(filename.find('.')!=string::npos)
    {
        newname=filename.substr(0,filename.find('.'));
    }
    else
    {
        newname=filename;
    }
    newname+=exten;
    return newname;
}

void checksavefile(string &filename,string exten)
{


    ifstream in;
    bool check=false;
    string line;
    in.open(filename);
    while(!check)
    {
        if(in.is_open())
        {
            in.close();
            cout<<"the file "<<filename<<" already exist do you wish to override? ";
            getinput(cin,line);
            if(tolower(line[0])=='y')
            {
                cout<<"overriding"<<endl;
                check= true;
            }
            else
            {

                cout<<"enter a new file name: ";
                line=string();
                getinput(cin,line);
                filename= extension(line,exten);
                in.open(filename);
                if(in.is_open())
                    check=false;
                else
                    check= true;


            }
        }
        else
            check=true;
    }
    cout<<"saving to "<<filename<<endl;
    in.close();


}

void readexefile(ifstream &in, vector<string> &command)
{
    string line;
    while(!in.eof())
    {
        getinput(in,line);
        command.push_back(line);
    }
}

void getinput(istream& in, string &input)
{
    stringstream ss;
    string line;
    input=string();
    getline(in,line);
    ss<<line;
    while(ss>>line)
    {
        input=input+line+' ';
    }

    input=input.substr(0,input.length()-1);

}

void help()
{
    cout<<endl;
    cout<<"Please enter your command like this: "<<endl;
    cout<<"Valid Command: LET, PRINT, SAVE, LOAD, EXIT, WEXIT, Mag(A), Trig(A)"<<endl;
    cout<<"EXPAMPLES: "<<endl;
    cout<<"LET F = 3 2/3 - 1 2/9i"<<endl;
    cout<<"Mag(F) to find the magnitude of a complex number "<<endl;
    cout<<"Trig(F) to show the polar version of a complex number "<<endl;
    cout<<"F =G+H"<<endl;
    cout<<endl;
}
