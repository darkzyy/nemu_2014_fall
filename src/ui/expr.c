#include "common.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, plus='+', min='-', time='*', div='/', EQ, NUM, l='(', r= ')',NEG=0,DEREF

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	{"[0-9]+", NUM},
	{" +", NOTYPE},				// white space
	{"\\*", '*'},
	{"\\/", '/'},
	{"\\+", '+'},					// plus
	{"\\-", '-'},
	{"\\(", '('},
	{"\\)", ')'},
	{"==", EQ}						// equal
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
				Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				position += substr_len;
				int j;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */
				switch(rules[i].token_type) {
					case NOTYPE: break;
					case NUM: 
							for(j=0;j<substr_len;j++){
								tokens[nr_token].str[j]=substr_start[j];
							}
							tokens[nr_token].str[j]='a';
							tokens[nr_token].type=NUM;
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
	int i=0,x=0,y=1;
	printf("%c %c %c %c\n",tokens[p].str[0],tokens[p].str[1],tokens[p].str[2],tokens[p].str[3]);
	while(tokens[p].str[i]!='a'){
		i++;
	}
	i--;
	while(i>=0){
		x+=(tokens[p].str[i]+1-'1')*y;
		i--;
		y*=10;
	}
	printf("c 2 i suc,x=%d\n",x);
	fflush(stdout);
	return x;
}
const int top=10000;

static int domin_op(int p,int q){
	printf("finding domin op\n");
	fflush(stdout);
	int a[32];
	int stage=0,i=p,j=0,deep=100;
	for(;j<32;j++)
		a[j]=top;//一个足够大的数
	while(i<=q){
		if(tokens[i].type == '+'||tokens[i].type == '-')
			a[i]=stage+1;
		else if(tokens[i].type =='*'||tokens[i].type =='/')
			a[i]=stage+2;
		else if(tokens[i].type ==NEG){
			a[i]=top-deep+stage+1;
			deep--;
		}
		else if(tokens[i].type =='('){
			stage+=2;
			deep=100;
		}
		else if(tokens[i].type ==')')
			stage-=2;
		else if(tokens[i].type ==NUM)
			deep=100;
		i++;
	}
	i=q;
	int min=q;
	while(i>=p){
		if(a[i]<a[min])
			min=i;
		i--;
	}
	printf("-------------------\n");
	for(i=p;i<=q;i++){
		printf("%d	%d	",a[i],tokens[i].type);
	}
	printf("\n-------------------\n");
	printf("found=%d\n",min);
	return min;
}
static int eval(int p,int q){
	printf("evaluating\np=%d,q=%d\n",p,q);
	fflush(stdout);
	if(p>q){
		if((q!=p-1)||tokens[p].type!=NEG){
			printf("bad expr\n");
			assert(0);
		}
		else
			return 0;
	}
	else if(p==q){
		printf("p=q\n");
		return char2int(p);
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
			case NEG:return -val2;
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
	printf("%d\n",eval(p,q));

	/* TODO: Implement code to evaluate the expression. */
	return 0;
}

