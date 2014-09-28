#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_, *tail, *ftail;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
	}
	ftail =&bp_pool[i];
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
	tail = NULL;
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
		tail->next =free_;
		tail=tail->next;
	}
	free_=free_->next;
	tail->addr=addr;
	tail->pre_inc=inc;
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
		ftail->next=NULL;
		reno();			/*重置free_断点序号*/
		printf("返回成功\n");
	}
	else{/*第一个结点为NO*/
		p->NO=ftail->NO+1;
		ftail->next=head;
		ftail=ftail->next;
		head=head->next;
		p=head;
		p->NO--;
		while(p->next!=NULL){/*重置head中的序号*/
			p=p->next;
			p->NO--;
		}
		ftail->next=NULL;
		reno();
		printf("返回成功(head =NULL)\n");
	}

}





/* TODO: Implement the function of breakpoint */
