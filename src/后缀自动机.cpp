struct State {
	int length;
	State *parent,*go[C];
	State(int length = 0):length(length),parent(NULL){
		memset(go,0,sizeof(go));
	}
	State* extend(State*, int token);
} node_pool[V], *tot_node;
State* State::extend(State *start,int token){
	State *p=this;
	State *np=new(tot_node++) State(this->length+1);
	while(p!=NULL&&p->go[token]==NULL)
		p->go[token]=np, p=p->parent;
	if(p==NULL) np->parent=start;
	else{
		State *q=p->go[token];
		if(p->length+1==q->length) np->parent=q;
		else{
			State *nq=new(tot_node++) State(p->length+1);
			memcpy(nq->go,q->go,sizeof(q->go));
			nq->parent=q->parent;
			np->parent=q->parent=nq;
			while(p!=NULL&&p->go[token]==q)
				p->go[token]=nq, p=p->parent;
		}
	}
	return np;
}
