#include "common.h"
#include "cpu/reg.h"
#include "memory.h" 
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, plus='+', min='-', time='*', div='/',mod='%', l='(', r=')',EQ=0,NEQ,LESS,MORE,LESSEQ,MOREEQ, NUM, HNUM,REG,OR,AND,BOR,BXOR,BAND,LSFT,RSFT,BN,BANG,DEREF,NEG
	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	{"\\$[a-z]{2,3}", REG},			//0
	{"0[Xx][[:xdigit:]]+", HNUM},
	{"[0-9]+", NUM},
	{" +", NOTYPE},				// white space
	{"\\*", '*'},
	{"\\/", '/'},					//5
	{"\\+", '+'},					// plus
	{"\\-", '-'},
	{"\\(", '('},
	{"\\)", ')'},
	{"\\^",BXOR},					//10
	{"<<",LSFT},					
	{">>",RSFT},
	{"==", EQ},						// equal
	{"!=",NEQ},
	{">=",MOREEQ},					//15
	{"<=",LESSEQ},					
	{"<",LESS},
	{">",MORE},
	{"\\|{2}",OR},						
	{"\\&{2}",AND},					//20
	{"\\&",BAND},
	{"\\|",BOR},
	{"\\%",'%'},
	{"\\~",BN},
	{"\\!",BANG}					//25

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;
				//Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				assert(substr_len);
				position += substr_len;
				int j;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */
				switch(rules[i].token_type) {
					case NOTYPE: break;
					case REG:
							for(j=1;j<substr_len;j++){
								tokens[nr_token].str[j-1]=substr_start[j];
							}
							tokens[nr_token].str[j-1]='\0';
							tokens[nr_token].type=REG;
							nr_token++;
							break;				
					case NUM: 
							for(j=0;j<substr_len;j++){
								tokens[nr_token].str[j]=substr_start[j];
							}
							tokens[nr_token].str[j]='\0';
							tokens[nr_token].type=NUM;
							nr_token++;
							break;
					case DEREF: 
							tokens[nr_token].type=DEREF;
							nr_token++;
							break;
					case HNUM:
							for(j=0;j<substr_len;j++){
								tokens[nr_token].str[j]=substr_start[j];
							}
							tokens[nr_token].str[j]='\0';
							tokens[nr_token].type=HNUM;
							nr_token++;
							break;
					case '+':
						tokens[nr_token].type='+';
						nr_token++;
						break;
					case '-':
						tokens[nr_token].type='-';
						nr_token++;
						break;
					case '*':
						tokens[nr_token].type='*';
						nr_token++;
						break;
					case '/':
						tokens[nr_token].type='/';
						nr_token++;
						break;
					case '(':
						tokens[nr_token].type='(';
						nr_token++;
						break;
					case ')':
						tokens[nr_token].type=')';
						nr_token++;
						break;
					case EQ:
						tokens[nr_token].type=EQ;
						nr_token++;
						break;
					case NEQ:
						tokens[nr_token].type=NEQ;
						nr_token++;
						break;
					case LESS:
						tokens[nr_token].type=LESS;
						nr_token++;
						break;
					case MORE:
						tokens[nr_token].type=MORE;
						nr_token++;
						break;
					case MOREEQ:
						tokens[nr_token].type=MOREEQ;
						nr_token++;
						break;
					case LESSEQ:
						tokens[nr_token].type=LESSEQ;
						nr_token++;
						break;
					case OR:
						tokens[nr_token].type=OR;
						nr_token++;
						break;
					case AND:
						tokens[nr_token].type=AND;
						nr_token++;
						break;
					case BOR:
						tokens[nr_token].type=BOR;
						nr_token++;
						break;
					case BXOR:
						tokens[nr_token].type=BXOR;
						nr_token++;
						break;
					case BAND:
						tokens[nr_token].type=BAND;
						nr_token++;
						break;
					case LSFT:
						tokens[nr_token].type=LSFT;
						nr_token++;
						break;
					case RSFT:
						tokens[nr_token].type=RSFT;
						nr_token++;
						break;
					case '%':
						tokens[nr_token].type='%';
						nr_token++;
						break;
					case BN:
						tokens[nr_token].type=BN;
						nr_token++;
						break;
					case BANG:
						tokens[nr_token].type=BANG;
						nr_token++;
						break;

					default: assert(0);
				}
				
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
	return true; 
}
static bool check_parentheses(int p,int q){
	int l=0,r=0,i=p;
	while(i<=q){
		if(tokens[i].type=='(')
			l++;
		else if(tokens[i].type==')')
			r++;
		if(r>l){
			printf("sth wrong:))(\n");
			assert(0);
		}
		i++;
	}
	if(r<l){
		printf("sth wrong:(()\n");
		assert(0);
	}
	else if(r==l){
		if(tokens[p].type=='('&&tokens[q].type==')')
			return true;
	}
	return false;
}
static int char2int(int p){
	int x=0;
	sscanf(tokens[p].str,"%d",&x);
	return x;
	/*int i=0,x=0,y=1;
	//printf("%c %c %c %c\n",tokens[p].str[0],tokens[p].str[1],tokens[p].str[2],tokens[p].str[3]);
	while(tokens[p].str[i]!='\0'){
		i++;
	}
	i--;
	while(i>=0){
		x+=(tokens[p].str[i]+1-'1')*y;
		i--;
		y*=10;
	}
	//printf("c 2 i suc,x=%d\n",x);
	fflush(stdout);
	return x;*/
}
static int hex210(int p){
	int x=0;
	sscanf(tokens[p].str,"%x",&x);
	return x;
	/*int i=0,x=0,y=1;
	//printf("%c %c %c %c\n",tokens[p].str[0],tokens[p].str[1],tokens[p].str[2],tokens[p].str[3]);
	while(tokens[p].str[i]!='a'){
		i++;
	}
	i--;
	while(tokens[p].str[i]!='x'&&tokens[p].str[i]!='X'){
		if(tokens[p].str[i]>='A'&&tokens[p].str[i]<='F')
				x+=(tokens[p].str[i]-'A'+10)*y;
		else if(tokens[p].str[i]>='a'&&tokens[p].str[i]<='f')
				x+=(tokens[p].str[i]-'a'+10)*y;
		else
				x+=(tokens[p].str[i]+1-'1')*y;

		i--;
		y*=16;
	}
	//printf("hex 2 10 suc,x=%d\n",x);
	fflush(stdout);
	return x;*/
}
static int reg2int(int p){
	/*if(tokens[p].str[2]=='a'&&tokens[p].str[3]=='x')
		return cpu.eax;
	else if(tokens[p].str[2]=='c'&&tokens[p].str[3]=='x')
		return cpu.ecx;
	else if(tokens[p].str[2]=='d'&&tokens[p].str[3]=='x')
		return cpu.edx;
	else if(tokens[p].str[2]=='b'&&tokens[p].str[3]=='x')
		return cpu.ebx;
	else if(tokens[p].str[2]=='s'&&tokens[p].str[3]=='p')
		return cpu.esp;
	else if(tokens[p].str[2]=='b'&&tokens[p].str[3]=='p')
		return cpu.ebp;
	else if(tokens[p].str[2]=='s'&&tokens[p].str[3]=='i')
		return cpu.esi;
	else if(tokens[p].str[2]=='d'&&tokens[p].str[3]=='i')
		return cpu.edi;*/
	int i;
	for(i=0;i<8;i++){
		if(strcmp(tokens[p].str,regsl[i])==0)
			return reg_l(i);
	}
	for(i=0;i<8;i++){
		if(strcmp(tokens[p].str,regsw[i])==0)
			return reg_w(i);
	}
	for(i=0;i<8;i++){
		if(strcmp(tokens[p].str,regsb[i])==0)
			return reg_b(i);
	} 
	printf("bad reg request\n");
	return 0;
	
}

const int top=10000;

static int domin_op(int p,int q){
	//printf("finding domin op\n");
	//fflush(stdout);
	int a[32];
	int stage=0,i=p,j=0;
	for(;j<32;j++)
		a[j]=top;//一个足够大的数
	while(i<=q){
		if(tokens[i].type == '+'||tokens[i].type == '-')
			a[i]=stage+9;
		else if(tokens[i].type =='*'||tokens[i].type =='/'||tokens[i].type =='%')
			a[i]=stage+10;
		else if(tokens[i].type ==NEG||tokens[i].type ==BN||tokens[i].type ==BANG||tokens[i].type ==DEREF)
			a[i]=stage+11;
		else if(tokens[i].type == LSFT||tokens[i].type == RSFT)
			a[i]=stage+8;
		else if(tokens[i].type ==LESS||tokens[i].type ==MORE||tokens[i].type ==LESSEQ||tokens[i].type ==MOREEQ)
			a[i]=stage+7;
		else if(tokens[i].type ==EQ||tokens[i].type ==NEQ)
			a[i]=stage+6;
		else if(tokens[i].type ==BAND)
			a[i]=stage+5;
		else if(tokens[i].type ==BXOR)
			a[i]=stage+4;
		else if(tokens[i].type ==BOR)
			a[i]=stage+3;
		else if(tokens[i].type ==AND)
			a[i]=stage+2;
		else if(tokens[i].type ==OR)
			a[i]=stage+1;
		else if(tokens[i].type =='('){
			stage+=12;
		}
		else if(tokens[i].type ==')')
			stage-=12;
		i++;
	}
	i=q;
	int min=q;
	while(i>=p){
		if(a[min]%12==11){
			if(a[i]<=a[min])
				min=i;
		}
		else{
			if(a[i]<a[min])
				min=i;
		}
		i--;
	}
	/*printf("-------------------\n");
	for(i=p;i<=q;i++){
		printf("%d	%d	",a[i],tokens[i].type);
	}
	printf("\n-------------------\n");*/
	//printf("found=%d\n",min);
	return min;
}
static int eval(int p,int q){
	//printf("evaluating:	p=%d,q=%d\n",p,q);
	fflush(stdout);
	if(p>q){
		if((q==p-1)&&(tokens[p].type==NEG||tokens[p].type==BN||tokens[p].type==BANG||tokens[p].type==DEREF)){
			return 0;
		}
		else
			printf("bad expr\n");
			assert(0);
	}
	else if(p==q){
		if(tokens[p].type==NUM)
			return char2int(p);
		else if(tokens[p].type==HNUM)
			return hex210(p);
		else 
			return reg2int(p);
	}
	else if(check_parentheses(p,q)==true){
		return eval(p+1,q-1);
	}
	else{
		int op=domin_op(p,q);
		int val1=eval(p,op-1);
		int val2=eval(op+1,q);
		switch(tokens[op].type){
			case '+':return val1+val2;
			case '-':return val1-val2;
			case '*':return val1*val2;
			case '/':return val1/val2;
			case '%':return val1%val2;
			case EQ:return val1==val2;
			case NEQ:return val1!=val2;
			case LESS:return val1<val2;
			case MORE:return val1>val2;
			case LESSEQ:return val1<=val2;
			case MOREEQ:return val1>=val2;
			case OR:return val1||val2;
			case AND:return val1&&val2;
			case BOR:return val1|val2;
			case BAND:return val1&val2;
			case BXOR:return val1^val2;
			case LSFT:return val1<<val2;
			case RSFT:return val1>>val2;
			case NEG:return -val2;
			case BANG:return !val2;
			case BN:return ~val2;
			case DEREF:return swaddr_read(val2,1);
			default:assert(0);
		}
	}
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	int i;
	for(i=0;i<nr_token;i++){
		if(tokens[i].type=='-'&&(i==0||tokens[i-1].type==NEG||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='*'||tokens[i-1].type=='/'||tokens[i-1].type=='(')){
			tokens[i].type=NEG;
		}
	}
	for(i=0;i<nr_token;i++){
		if(tokens[i].type=='*'&&(i==0||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='*'||tokens[i-1].type=='/'||tokens[i-1].type=='(')){
			tokens[i].type=DEREF;
		}
	}
	uint32_t p=0,q=nr_token-1;
	uint32_t val=eval(p,q);
	//printf("%d\n",val);

	/* TODO: Implement code to evaluate the expression. */
	return val;
}

