#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#define F first
#define S second

ll d, t;

class Node{
	public:
		vector<ll> key;
		vector<Node*> childrenNode;
		bool isLeaf;
		Node* rightNode;
		Node* leftNode;
		Node* parentNode;
		Node(){
			key={};
			childrenNode={};
			isLeaf=false;
			rightNode=NULL;
			leftNode=NULL;
			parentNode=NULL;
		}
};

class BPT{
	public:
		ll nd, ni;
		Node* root;
		BPT(){
			root=new Node();
			root->isLeaf=true;
			nd=1;ni=0;
		}
		void BPTsplit(Node* x){
			// // debug(x->key,x->isLeaf);
			if (x->isLeaf){
				nd++;
				ll sep=(x->key)[d];
				Node* a=new Node();
				Node* b=new Node();
				a->isLeaf=true;
				b->isLeaf=true;
				for (ll i=0; i<d; i++){
					(a->key).push_back((x->key)[i]);
				}
				for (ll i=d; i<=2*d; i++){
					(b->key).push_back((x->key)[i]);
				}
				if (x->parentNode==NULL){
					// // debug(x->key);
					ni++;
					Node* temp=new Node();;
					root=temp;
					(root->key).push_back(sep);
					a->parentNode=root;b->parentNode=root;
					(root->childrenNode).push_back(a);
					(root->childrenNode).push_back(b);
				}
				else{
					Node* p=x->parentNode;
					// // debug(p->key);
					ll n=(p->childrenNode).size();
          ll in=0;
          while(in<n){
            if ((p->childrenNode)[in]==x) break;
            in++;
          }

          // // temp is the new p->childrenNode vector
          // vector<Node*> temp;
					// for (ll i=0; i<in; i++) temp.push_back((p->childrenNode)[i]);
					// temp.push_back(a);temp.push_back(b);
					// for (ll i=in+1; i<n; i++) temp.push_back((p->childrenNode)[i]);
					// p->childrenNode=temp;
					// a->parentNode=p;b->parentNode=p;
					// (p->key).push_back(sep);
					// sort((p->key).begin(),(p->key).end());

          (p->childrenNode).erase((p->childrenNode).begin()+in);
          (p->childrenNode).insert((p->childrenNode).begin()+in,{a,b});
          a->parentNode=p;b->parentNode=p;
          (p->key).insert((p->key).begin()+in,sep);

					if ((p->key).size()>2*t+1) BPTsplit(p);
				}
			}
			else{
				ni++;
				Node* a=new Node();
				Node* b=new Node();
				Node* p=x->parentNode;
				ll y=(x->key)[t];

				for (ll i=0; i<t; i++){
					(a->key).push_back((x->key)[i]);
				}
				for (ll i=t+1; i<2*t+2; i++){
					(b->key).push_back((x->key)[i]);
				}
				for (ll i=0; i<=t; i++){
					(a->childrenNode).push_back((x->childrenNode)[i]);
					((x->childrenNode)[i])->parentNode=a;
				}
				for (ll i=t+1; i<=2*t+2; i++){
					(b->childrenNode).push_back((x->childrenNode)[i]);
					((x->childrenNode)[i])->parentNode=b;
				}
				if (p==NULL){
					// // debug(x->key);
					ni++;
					Node* temp=new Node();;
					root=temp;
					(root->key).push_back(y);
					a->parentNode=root;b->parentNode=root;
					(root->childrenNode).push_back(a);
					(root->childrenNode).push_back(b);
				}
				else{
					ll n=(p->childrenNode).size();
					
					ll in=0;
          while(in<n){
            if ((p->childrenNode)[in]==x) break;
            in++;
          }

          // vector<Node*> temp;
					// for (ll i=0; i<in; i++) temp.push_back((p->childrenNode)[i]);
					// temp.push_back(a);temp.push_back(b);
					// for (ll i=in+1; i<n; i++) temp.push_back((p->childrenNode)[i]);
					// p->childrenNode=temp;
					// a->parentNode=p;b->parentNode=p;
					// // // debug(p->key);
					// (p->key).push_back(y);
					// sort((p->key).begin(),(p->key).end());

          (p->childrenNode).erase((p->childrenNode).begin()+in);
          (p->childrenNode).insert((p->childrenNode).begin()+in,{a,b});
          a->parentNode=p;b->parentNode=p;
          (p->key).insert((p->key).begin()+in,y);

          if ((p->key).size()>2*t+1) BPTsplit(p);
				}
			}
		}
		void BPTinsertval(Node* x, ll val){
			// // debug(root->key);
			// // debug(x->key);
			// if (x->parentNode!=NULL) {
			// 	// // debug((x->parentNode)->key);
			// }
			if (!x->isLeaf){
				auto it=upper_bound((x->key).begin(),(x->key).end(),val) - (x->key).begin();
				BPTinsertval((x->childrenNode)[it],val);
			}
			else{
				// // debug(x->key);
        (x->key).push_back(val);
				sort((x->key).begin(),(x->key).end());

				if ((x->key).size()>2*(d)){	
					BPTsplit(x);
				}
			}
		}
		void BPTprint(){
			// cout<<ni<<" "<<nd<<" ";
			for (auto u: root->key) cout<<u<<" ";
			// cout<<endl;
		}
		pair<ll,ll> BPTcount(Node* x, ll ci, ll cd){
			// debug(x->key,x->isLeaf);
			if (x->isLeaf) cd++;
			else{
				ci++;
				for (auto u: x->childrenNode){
					pair<ll,ll> z=BPTcount(u,0ll,0ll);
					ci+=z.F;
					cd+=z.S;
				}
			}
			return {ci,cd};
		}
};

int main(){
	cin>>d>>t;
	ll x;
	ll fl=0;
	BPT tree;
	while (cin>>x){
		if (x==1){
			fl=1;
			ll y;
			cin>>y;
			// // debug(y);
			tree.BPTinsertval(tree.root,y);
		}
		else if (x==2){
			// // debug(true);
			pair<ll,ll> a=tree.BPTcount(tree.root,0,0);
			// if (fl) tree.BPTprint();
			// else cout<<0<<" "<<0<<endl;
			if (fl==0) cout<<"0 0";
			else cout<<a.F<<" "<<a.S<<" ";
			tree.BPTprint();
			cout<<endl;
		}
		else break;
	}
	return 0;
}
