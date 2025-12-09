//Hassan Hassoun
//Programming assignment 2
//7/19/2025

#include <iostream>
#include <string>
#include<vector>

using namespace std;

class Person {
private:
	int age;
	int marriage;
	string name;
	string spouse;
	int num_parent;
	string parent[2];
	int num_children;
	string children[10];

public:

	Person() {
		age = 0;
		marriage = 2;
		name = "unknown";
		spouse = "none";
		num_parent = 2;
		parent[0] = "unknown";
		parent[1] = "unknown";
		num_children = 0;

		for (int i = 0; i < 10; i++) {
			children[i] = "unknown";

		}
	}

	Person(int a, int b, string c, string d[], int e, string f[]) {
		age = a;
		marriage = b;
		name = c;
		spouse = "none";
		num_parent = 2;

		for (int i = 0; i < 2; i++) {
			parent[i] = d[i];
		}

		for (int i = 0; i < e; i++) {
			children[i] = f[i];
		}
	}

	void setAge(int a) {
		age = a;
	}
	void setMarriage(int m) {
		marriage = m;
	}
	void setName(string n) {
		name = n;
	}
	void setSpouse(string s) {
		spouse = s;

	}
	void setParent(string p[2]) {
		for (int i = 0; i < 2; i++) {
			parent[i] = p[i];
		}
	}
	void setChildren(int n, string c[]) {
		num_children = n;
		for (int i = 0; i < n; i++) {
			children[i] = c[i];
		}
	}

	int getAge() const {
		return age;
	}
	int getMarriage() const{
		return marriage;
	}
	string getName() const{
		return name;
	}
	string getSpouse() const{
		return spouse;
	}

	void getParent(string outParent[2]) const{
		for (int i = 0; i < 2; i++) {
			outParent[i] = parent[i];
		}
	}

	int getNumChildren() const{
		return num_children;
	}
	void getChildren(string outChildren[]) const{
		for (int i = 0; i < num_children; i++) {
			outChildren[i] = children[i];
		}
	}

};

void query(const string& targetName, const vector<Person>& family) {
	bool found = false;

	for (const Person& person : family) {
		if (person.getName() == targetName) {
			found = true;
			cout << "\nQuery result for: " << targetName << endl;

			string p[2];
			person.getParent(p);
			cout << "Parents: " << p[0] << ", " << p[1] << endl;

			int numChildren = person.getNumChildren();
			string children[10];
			person.getChildren(children);

			cout << "Children: ";
			if (numChildren == 0) {
				cout << "None";
			}
			else {
				for (int i = 0; i < numChildren; i++) {
					cout << children[i];
					if (i < numChildren - 1) {
						cout << ", ";
					}
				}
			}
			cout << endl;

			cout << "Grandchildren: ";
			bool hasGrandkids = false;
			for (int i = 0; i < numChildren; i++) {
				for (const Person& p : family) {
					if (p.getName() == children[i]) {
						int grandCount = p.getNumChildren();
						string grandkids[10];
						p.getChildren(grandkids);
						for (int j = 0; j < grandCount; j++) {
							cout << grandkids[j];
							if (j < grandCount - 1) {
								cout << ", ";
							}
							hasGrandkids = true;
						}
						break;
					}
				}
			}
			if (!hasGrandkids) {
				cout << "None";
			}
			cout << endl;
			break;
		}
	}

	if (!found) {
		cout << "Person named '" << targetName << "' not found." << endl;
	}
}

void sibling(const string& targetName, const vector<Person>& family) {
	string targetParents[2];
	bool found = false;

	for (const Person& person : family) {
		if (person.getName() == targetName) {
			person.getParent(targetParents);
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "\nPerson named ' " << targetName << "' not found.\n";

	}

	if (targetParents[0] == "unknown" && targetParents[1] == "unknown") {
		cout << "\n" << targetName << " has no known siblings (top of tree)." << endl;
		return;
	}


	cout << "\nSiblings of " << targetName << ": ";
	bool hasSiblings = false;
	for (const Person& person : family) {
		if (person.getName() != targetName) {
			string p[2];
			person.getParent(p);
			if ((p[0] == targetParents[0] && p[1] == targetParents[1]) ||
				(p[0] == targetParents[1] && p[1] == targetParents[0])) {
				cout << person.getName() << ", ";
				hasSiblings = true;

			}
		}
	}
	if (!hasSiblings)
		cout << "None";
	cout << endl;

}

int main() {

	string seanChildren[] = { "Conor Flaherty", "Brenda Flaherty" };
	string conorChildren[] = { "Mary Flaherty", "Michelle Fowler" };
	string brendaChildren[] = { "Mark Fowler" };
	string emptyChildren[10];
	string conorParents[] = { "Sean Flaherty", "Maggie Beale" };
	string brendaParents[] = { "Sean Flaherty", "Maggie Beale" };
	string maryParents[] = { "Conor Flaherty", "Geraldine Chaplin" };
	string michelleParents[] = { "Conor Flaherty", "Geraldine Chaplin" };
	string markParents[] = { "Brenda Flaherty", "Arthur Fowler" };
	string unknownParents[] = { "unknown", "unknown" };

	Person sean(70, 1, "Sean Flaherty", unknownParents, 2, seanChildren);
	Person maggie(68, 1, "Maggie Beale", unknownParents, 2, seanChildren);

	Person conor(44, 1, "Conor Flaherty", conorParents, 2, conorChildren);
	Person geraldine(42, 1, "Geraldine Chaplin", unknownParents, 2, conorChildren);
	
	Person brenda(41, 1, "Brenda Flaherty", brendaParents, 1, brendaChildren);
	Person arthur(43, 1, "Arthur Fowler", unknownParents, 1, brendaChildren);

	Person mary(18, 2, "Mary Flaherty", maryParents, 0, emptyChildren);
	Person michelle(17, 2, "Michelle Fowler", maryParents, 0, emptyChildren);
	Person mark(15, 2, "Mark Fowler", markParents, 0, emptyChildren);



	sean.setSpouse("Maggie Beale");
	maggie.setSpouse("Sean Flaherty");

	conor.setSpouse("Geraldine Chaplin");
	geraldine.setSpouse("Conor Flaherty");

	brenda.setSpouse("Arthur Fowler");
	arthur.setSpouse("Brenda Flaherty");

	vector<Person> family = {
		sean, maggie, conor, geraldine, brenda, arthur, mary, michelle, mark
	};

	cout << "The Query Test" << endl;
	query("Maggie Beale", family);
	query("Brenda Flaherty", family);




	cout << "Testing Siblings in Task 6" << endl;
	sibling("Geraldine Chaplin", family);
	sibling("Arthur Fowler", family);
	sibling("Conor Flaherty", family);
	sibling("Brenda Flaherty", family);


	return 0;
}