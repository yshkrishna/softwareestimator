  
    #include<iostream>
    #include<stdio.h>
    #include<ctype.h>
    #include<string.h>
    #include<math.h>


int h, ss[3],loc=0,cha=0;

float kloc, fp, E[3], D[3], P[3];
float a[3] = {2.4,3.0,3.6};
float b[3] = {1.05,1.12,1.20};
float c[3] = {2.5,2.5,2.5};
float d[3] = {0.38,0.35,0.32};
float EFA = 1, sw = 1;

void calc(int h)
{
  E[h] = a[h] * (pow(kloc , b[h]));
  D[h] = c[h] * (pow(E[h], d[h]));
  ss[h] = E[h] / D[h];
  P[h] = kloc / E[h];

  std::cout << "Effort, E= " << E[h] << " PM\n";
  std::cout << "Developed Time, D= " << D[h] << " M\n";
  std::cout << "StaffSize, ss= " << ss[h] << "% persons\n";
  std::cout << "Productivity, P= " << P[h] << " KLOC/PM\n";
}
     
    void keyw(char *p);
     
    int i = 0, id = 0, kw = 0, num = 0, op = 0;
     
    char keys[32][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
     
    int main() 
{
        char ch,str[25], seps[]= " \t\n,;(){}[]#\"<>", oper[]= "!%^&*-+=~|.<>/?";
        int j;
        char fname[50];
        FILE *f1;
       
        printf("Enter filename: ");
        scanf("%s",fname);
     
        f1 = fopen(fname,"r");
     
        if(f1==NULL)
        {
            printf("file not found");

        }
     
         /*  while((ch = getc(f1))! = EOF)
      {
       int c,l;

	c++;if(ch=='\n')
	l++;
      } */
       while ((ch = fgetc(f1)) != EOF)
            {
                

	        cha++;if(ch=='\n')
	           loc++;
                   
                for(j = 0; j <= 14; j++)
                    {
                        if(ch == oper[j])
                            {
                                //printf("%c is an operator\n", ch);
                                op++;
                                str[i]='\0';
                                keyw(str);
                            }
                    }
                for(j = 0; j <= 14; j++)
                    {
                        if(i == -1)
                            break;
                        if(ch == seps[j])
                            {
                                if(ch == '#')
                                    {
                                        while(ch != '>')
                                            {
                                                //printf("%c", ch);
                                        
                                                ch = fgetc(f1);
                                            }
                                  //      printf("%c is a header file\n", ch);
                                        i = -1;
                                        break;
                                    }
                                if(ch=='"')
                                    {
                                        do
                                            {
                                                ch=fgetc(f1);

                                               // printf("%c",ch);
                                            }
                                        while(ch!='"');
     
                                    //    printf("\b is an argument\n");
                                        i = -1;
                                        break;
                                    }
                                str[i] = '\0';
                                keyw(str);
                            }
                    }
                if(i != -1)
                    {
                        str[i] = ch;
                        i++;
                    }
                else
                    i = 0;
            }
         printf("characters:%d lines:%d",cha,loc);
        printf("Keywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\n",kw,id,op,num);
   
       fp=(kw+id+op+num)/4;
      
      printf("function points:%f",fp);

       
  std::cout << "COCOMO 1:\n";
  //std::cout << "Enter the number of Function Points: ";
  //std::cin >> fp;
  std::cout << "Multiplication factor for 'c' is 128 LOC/FP.\n";

  kloc = (fp * 128.00) / 100.00;

  std::cout << "KLOC = " << kloc << std::endl;
  std::cout << "Estimation:\n";
  std::cout << "For organic Mode:";
  calc(0);
  std::cout << "For Semidetatched Mode:\n";
  calc(1);
  std::cout << "For Embedded Mode:\n";
  calc(2);
  std::cout << "COCOMO 2:\n";
  std::cout << "Application Composition Model:\n";

  float reuse;

  std::cout << "Enter percentage of reuse: ";                   //it always any soft max 100% reuse
  std::cin >> reuse;

  // unsigned int nfp = (fp * (1 - reuse) /100);               //new function point
  int pmv = (fp * (1 - (reuse / 100)) / 4);                 //persons per month for very low,low,normal,high,very high
  int pml = (fp * (1- (reuse / 100)) / 7); 
  int pmn = (fp * (1 - (reuse / 100)) / 13); 
  int pmh = (fp * (1 - (reuse / 100)) / 25); 
  int pmvh = (fp * (1 - (reuse / 100)) / 50); 

  std::cout << "\nPersons per month:\n";
  std::cout << " persons per month very low" << pmv << " persons per month  low" << pml << " persons per month normal " << pmn << " persons per month high" << pmh << " persons per month very high" << pmvh << std::endl;

  std::cout << "\n The Early Design Model:\n";
  std::cout << "Enter 17 cost drives:\n";

  float cd1, cd2, cd3, cd4, cd5, cd6, cd7, cd8, cd9, cd10, cd11, cd12, cd13, cd14, cd15, cd16, cd17;

  std::cout << "1. Programmer capability: ";                       std::cin >> cd1;
  std::cout << "2. Required system Reliability: ";                 std::cin >> cd2;
  std::cout << "3. Complexity of system modules: ";                std::cin >> cd3;
  std::cout << "4. Extent of documentation required: ";            std::cin >> cd4;
  std::cout << "5. Size of database used: ";                       std::cin >> cd5;
  std::cout << "6. Required percentage of reusable components: ";  std::cin >> cd6;
  std::cout << "7. Execution time constraint: ";                   std::cin >> cd7;
  std::cout << "8. volatility of development platform: ";          std::cin >> cd8;
  std::cout << "9. Memory constraints: ";                          std::cin >> cd9;
  std::cout << "10. Capability of project analysts: ";             std::cin >> cd10;
  std::cout << "11. Personnel continuity: ";                       std::cin >> cd11;
  std::cout << "12. Programmer experience in project domain: ";    std::cin >> cd12;
  std::cout << "13. Analyst experience in project domain: ";       std::cin >> cd13;
  std::cout << "14. Language and tool experience: ";               std::cin >> cd14;
  std::cout << "15. Use of software tools: ";                      std::cin >> cd15;
  std::cout << "16. Development schedule compression: ";           std::cin >> cd16;
  std::cout << "17. Extent of multisite working and quality of inter-site communications: "; std::cin >> cd17;

  int eaff = (cd1 * cd2 * cd3 * cd4 * cd5 * cd6 * cd7 * cd8 * cd9 * cd10 * cd11 * cd12 * cd13 * cd14 * cd15 * cd16 * cd17);
 
  std::cout << "==> EAF = " << eaff << std::endl;

  std::cout << "The Post Architectural Model:\n";

  float sd1, sd2, sd3, sd4, sd5, e;
 
  std::cout << "Please input all 5 Scale Driver:\n";
  std::cout << "1. Precedentedness: ";
  std::cin >> sd1;
  std::cout << "2. Development Flexibility: ";
  std::cin >> sd2;
  std::cout << "3. Architeture/Rise Resolution: ";
  std::cin >> sd3;
  std::cout << "4. Team Cohesion: ";
  std::cin >> sd4;
  std::cout << "5. Process Maturity: ";
  std::cin >> sd5;
  
  e = 1.01 + (sd1 + sd2 + sd3 + sd4 + sd5);
  
  std::cout << "==> E = " << e << std::endl;
  std::cout << "Effort = 2.94 * EAF * (KSLOC)^E" << std::endl;
  std::cout << "Where KSLOC = LOC/1000"<< std::endl;

  //int loc = 10000; //TODO: Fix this with LOC code
  int ksloc = loc / 1000;

  std::cout << "KSLOC = " << ksloc << std::endl;
  
  unsigned int effort = 2.94 * eaff * pow(ksloc, e);

  std::cout << "Effort = "<< effort << " person-months" << std::endl;
//  std::cout << "Duration = 3.67 * (Effort)^SE"<< std::endl;
  //std::cout << "Where SE = 0.28 + 0.2 * (E - 1.01)" << std::endl;

  //float se = 0.28 + (0.2 * (e - 1.01));

//  std::cout << "==> SE = "<< se <<std::endl;

  //float duration = 3.67 * pow(effort,se);

  //std::cout << "Duration = "<< duration << " months" << std::endl;
  //std::cout << "Person = Effort / Duration" << std::endl;

  //int person = effort / duration;

  //std::cout << "Person = " << person << " people" << std::endl;
  std::cout << "Cost Estimation Completed." << std::endl;  
    }
     
    void keyw(char *p)
    {
        int k, flag=0;
        for(k=0; k <= 31; k++)
            {
                if (strcmp(keys[k], p) == 0)
                    {
                        //printf("%s is a keyword\n", p);
                        kw++;
                        flag = 1;
                        break;
                    }
            }
        if(flag == 0)
            {
                if (isdigit(p[0]))
                    {
                        //printf("%s is a number\n",p);
                        num++;
                    }
                else
                    {
                        //if(p[0]!=13&&p[0]!=10)
                        if (p[0] != '\0')
                            {
                                //printf("%s is an identifier\n", p);
                                id++;
                            }
                    }
            }
        i = -1;
    }


