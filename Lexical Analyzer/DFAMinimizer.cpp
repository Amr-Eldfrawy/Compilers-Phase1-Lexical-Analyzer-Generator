#include "DFAMinimizer.h"
#include "DFANode.h"
//#include "DFANode.cpp"

#include <queue>
#include <set>
#include <unordered_map>

DFAMinimizer::DFAMinimizer (){
	init = false;
}

DFAMinimizer::DFAMinimizer (DFA* dfa){
	DFAMinimizer::groups.resize(2);
	DFAMinimizer::dfa = dfa;
	init = true;
}


DFA* DFAMinimizer::minimize(){
	queue <DFANode*> q;
	set <DFANode*> s;

	q.push(dfa->head);
	s.insert (dfa->head);

	map <int, DFANode*> :: iterator map_it;
	map <string, int> mp;

	groups.clear();
	groups.push_back(*(new set<DFANode*>()));

	while (!q.empty()){
		DFANode* c = q.front();
		q.pop();

		if (!(c->acc)){
			DFAMinimizer::groups[0].insert(c);
			c->group = 0;
		}
		else{
			int ind;
			if (mp.find(c->token_name) == mp.end()){
				mp[c->token_name] = mp.size();
				set <DFANode*> new_state;
				groups.push_back(new_state);
			}
			ind = mp[c->token_name];
			c->group = ind;
			DFAMinimizer::groups[ind].insert(c);
		}

		for (map_it = c->matrix.begin();map_it != c->matrix.end(); ++map_it){
			if (s.find(map_it->second) != s.end())
				continue;
			s.insert (map_it->second);
			q.push(map_it->second);
		}
	}
	printf ("%d\n", s.size());
	printf ("size: %d\n", groups.size());
	
	bool operation_flag = true;
	set <DFANode*>::iterator it;
	
	while (operation_flag){
		operation_flag = false;

		for (size_t i=0;i<groups.size();i++){
			for (int l = 0; l < 256; l ++){
				unordered_map <int, int> m;
				m.clear();
				int f = 0;
				for (it = groups[i].begin(); it != groups[i].end(); ++it){
					if ((*it)->matrix.find(l) != (*it)->matrix.end())
						f++;
				}
				if (f && f != groups[i].size()){
					set <DFANode*> new_set;
					for (it = groups[i].begin(); it != groups[i].end(); ++it)
						if ((*it)->matrix.find(l) != (*it)->matrix.end()){
							(*it)->group = groups.size();
							new_set.insert (*it);
						}
					for (it = new_set.begin(); it != new_set.end(); ++it)
						groups[i].erase(*it);
					groups.push_back(new_set);
					operation_flag = true;
					goto stop;
				}
				if (!f)
					continue;
				for (it = groups[i].begin(); it != groups[i].end(); ++it){
					if (m.find(((*it)->matrix[l])->group) == m.end())
						m[((*it)->matrix[l])->group] = m.size();
				}
				for (size_t j=1;j<m.size();j++){
					set <DFANode*> new_set;
					for (it = groups[i].begin(); it != groups[i].end(); ++it)
						if (m[((*it)->matrix[l])->group] == j){
							new_set.insert(*it);
							(*it)->group = groups.size();
						}
					for (it = new_set.begin(); it != new_set.end(); ++it)
						groups[i].erase(*it);
					groups.push_back(new_set);
					operation_flag = true;
				}
			}	
		}

		stop:
		printf ("size: %d\n", groups.size());
		continue;
	}

	vector <DFANode*> nodes;

	for (size_t i=0; i< groups.size(); i++){
		DFANode* newNode = new DFANode();
		newNode->id = i;
		nodes.push_back(newNode);
	}

	for (size_t i=0;i<groups.size();i++){
		DFANode* c = *(groups[i].begin());
		int ind = c->group;
		for (int l=0;l<256;l++)
			if (c->matrix.find(l) != c->matrix.end())
				nodes[ind]->matrix[l] = nodes[(c->matrix[l])->group];
		for (it = groups[i].begin(); it != groups[i].end(); it++){
			c = *it;
			if ((c->token_priority) >= (nodes[i]->token_priority)){
				nodes[i]->token_priority = c->token_priority;
				nodes[i]->token_name = c->token_name;
			}
			if (c->acc)
				nodes[i]->acc = true;
		}
	}

	DFAMinimizer::dfa->head = nodes[(DFAMinimizer::dfa->head)->group];

	cout << "FINAL " << groups.size() << " nodes" << endl;

	return DFAMinimizer::dfa;
}
