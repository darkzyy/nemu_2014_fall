#include "ui/breakpoint.h"

#include "nemu.h"
#include <string.h>
#include <stdlib.h>
#define NR_BP 32
extern uint32_t expr(char *e,bool *success);
static BP bp_pool[NR_BP];
static BP *head, *free_, *tail, *ftail;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].type = 0;
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
		bp_pool[i].addr =0;
		bp_pool[i].pre_inc=0;
		bp_pool[i].pre_val=0;
		sscanf("\0","%s",bp_pool[i].exp);
	}
	ftail =&bp_pool[i];
	ftail->NO=i;
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
	tail = NULL;
}
swaddr_t find_bp(int a){
	assert(head);
	BP *p=head;
	while(a!=1){
		a--;
		if(p->next!=NULL)
		  p=p->next;
		else
		  printf("error input\n");
	}
	return p->addr;
}
void printb(){
	int i=1;
	if(head==NULL){
		printf("bpbool=NULL \n");
		return;
	}
	BP *p=head;
	if(p->type==0)
	  printf("%d:		addr:%x		inc:%x\n",i,p->addr,p->pre_inc);
	else
	  printf("%d:		watchpoint:%s		pre_val:%d\n",i,p->exp,p->pre_val);
	while(p!=tail){
		p=p->next;
		i++;
		if(p->type==0)
		  printf("%d:		addr:%x		inc:%x\n",i,p->addr,p->pre_inc);
		else
		  printf("%d:		watchpoint:%s		pre_val:%d\n",i,p->exp,p->pre_val);
	}
}

int find_pre_inc(swaddr_t eip){
	if(head->addr==eip)
	  return head->pre_inc;
	BP *p=head;
	while(p!= tail){
		p=p->next;
		if(p->addr==eip)
		  return p->pre_inc;
	}
	if(head==tail){
		printf("eip error\n");
		return 0;
	}
	printf("unknown error\n");
	return 0;
}

void reno(){
	if(free_==NULL){printf("free_ NULL");}
	else {
		BP *p=free_;
		p->NO--;
		while(p->next!=NULL){
			p=p->next;
			p->NO--;
		}
	}
}
void add_bp(swaddr_t addr,int inc){
	if(free_->next==NULL){
		printf("free_已用尽/n");
		return;	
	};
	if(head==NULL){
		head =free_;
		tail=free_;
	}
	else {
		if(head->addr==addr){
			printf("already exists\n");
			return;
		}
		BP *p=head;
		while(p!=tail){
			p=p->next;
			if(p->addr==addr){
				printf("already exists\n");
				return;
			}
		}

		tail->next =free_;
		tail=tail->next;
	}
	free_=free_->next;
	tail->addr=addr;
	tail->pre_inc=inc;
	tail->next=NULL;
}
void add_wp(char *exp){
	if(free_->next==NULL){
		printf("free_已用尽\n");
		return;	
	};
	if(head==NULL){
		head =free_;
		tail=free_;
	}
	else {
		if(head->type==1&&strcmp(exp,head->exp)==0){
			printf("already exists\n");
			return;
		}
		BP *p=head;
		while(p!=tail){
			p=p->next;
			if(p->type==1&&strcmp(exp,p->exp)==0){
				printf("already exists\n");
				return;
			}
		}

		tail->next =free_;
		tail=tail->next;
	}
	free_=free_->next;
	//printf("166\n");fflush(stdout);
	tail->exp=strdup(exp);
	bool suc=0;
	tail->pre_val=expr(tail->exp,&suc);
	tail->type=1;
	//printf("%d\n",tail->pre_val);
	tail->next=NULL;
}
void free_bp(int NO){
	if(head==NULL){/*第一个节点空*/
		printf("head NULL");
		return;
	}
	BP *p=head;
	if(p->NO!=NO){
		while(p->next!=NULL){/*p有后继时*/
			if(p->next->NO==NO)
			  break;
			p=p->next;
		}
		if(p->next==NULL){/*所删除的NO不存在*/
			printf("bp%d doen't exist\n",NO);
			return ;
		}
		p->next->NO=ftail->NO+1;
		p->next->addr=0;
		p->next->type = 0;
		p->next->pre_val =0;
		p->next->pre_inc=0;
		free(p->next->exp);
		sscanf("\0","%s",p->next->exp);
		ftail->next=p->next;
		ftail=ftail->next;
		if (p->next->next!=NULL){
			p->next=p->next->next;
			while(p->next!=NULL){/*重置head中的序号*/
				p=p->next;
				p->NO--;
			}
		}
		else
		  p->next=NULL;
		tail=p;
		ftail->next=NULL;
		reno();			/*重置free_断点序号*/
		printf("返回成功\n");
	}
	else{/*第一个结点为NO*/
		p->NO=ftail->NO+1;
		p->addr=0;
		p->type =0;
		p->pre_val=0;
		p->pre_inc=0;
		free(p->exp);
		sscanf("\0","%s",p->exp);
		ftail->next=head;
		ftail=ftail->next;
		if(head->next!=NULL){
			head=head->next;
			p=head;
			p->NO--;
			while(p->next!=NULL){/*重置head中的序号*/
				p=p->next;
				p->NO--;
			}
			tail=p;
			ftail->next=NULL;
			reno();
			printf("返回成功(head !=NULL)\n");
		}
		else{
			head=NULL;
			tail=NULL;
			reno();
			printf("返回成功(head =NULL)\n");
		}
	}

}
bool wp_change(){
	if(head==NULL){
		return 0;
	}
	bool *suc=0;
	if(head->type==1&&expr(head->exp,suc)!=head->pre_val){
		printf("watchpoint	%d:%s\npre_val:%x	now:%x\n",head->NO+1,head->exp,head->pre_val,expr(head->exp,suc));
		head->pre_val=expr(head->exp,suc);
		return 1;
	}
	BP *p=head;
	while(p!=tail){
		p=p->next;
		if(p->type==1&&expr(p->exp,suc)!=p->pre_val){
			printf("watchpoint	%d:%s\npre_val:%x	now:%x\n",p->NO+1,p->exp,p->pre_val,expr(p->exp,suc));
			p->pre_val=expr(p->exp,suc);
			return 1;
		}
	}
	return 0;

}
void reload(){
	if(head==NULL)
	  return;
	if(head->type==0){
	  //printf("reloading\n");
		head->pre_inc=swaddr_read(head->addr,1);
		swaddr_write(head->addr,1,0xcc);
	}
	if(head->next==NULL)
	  return;
	else{
		BP *p=head;
		while(p->next!=NULL){
			p=p->next;
			if(p->type==0){
				//printf("reloading\n");
				p->pre_inc=swaddr_read(p->addr,1);
				swaddr_write(p->addr,1,0xcc);
			}
		}
		return;
	}
}

void add_newb(swaddr_t addr){
	if(free_->next==NULL){
		printf("free_已用尽\n");
		return;	
	};
	if(head==NULL){
		head =free_;
		tail=free_;
	}
	else{
		tail->next = free_;
		tail=tail->next;
	}
	free_= free_->next;
	tail->addr = addr;
	tail->type = 2;
	tail->next = NULL;
}
bool hit_newb(){
	if(head==NULL)
	  return 0;
	if(head->type ==2&&cpu.eip==head->addr){
		printf("newb hit!	addr:0x%x\n",head->addr);
		return 1;
	}
	BP *p=head;
	while(p!=tail){
		p=p->next;
		if(p->type ==2&&cpu.eip==p->addr){
			printf("newb hit!	addr:0x%x\n",p->addr);
			return 1;
		}
	}
	return 0;
}





	/* TODO: Implement the function of breakpoint */
