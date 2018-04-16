#include "resource.h"
#include <functional>
#define INF 100000 
using namespace std;

int Vertex::Total_Number = 0;
int Edge::Total_Number = 0;


//The constructor of the class Vertex;
Vertex::Vertex(string target_data, string target_des) {
	this->Data = target_data;
	this->Description = target_des;
	Total_Number++;
	this->Number = Total_Number;
	cout << "\n\tNo." << this->Number << " Spot \"" << this->Data << "\" is constructed successfully.\n";
}


Vertex::~Vertex() {
	cout << "\n\tNo." << this->Number << " Spot \"" << this->Data << "\" is destructed successfully.\n";
	Total_Number--;
}

void Vertex::Set_Data(string target_data) {
	this->Data = target_data;
}

string Vertex::Get_Data(void) const {
	return this->Data;
}

void Vertex::Set_Description(string subdes) {
	this->Description = subdes;
}

string Vertex::Get_Description(void) const {
	return this->Description;
} 

int Vertex::Get_Number(void) const {
	return this->Number;
}

bool Vertex::Is_Adjacent(string target_vertex_data) const {
	for(int i = 0; i < this->Adjacency_Vertex.size(); ++i) {
		if(target_vertex_data == this->Adjacency_Vertex[i].first)
			return true;
	}
	return false;
}

void Vertex::Display_Information() const {
	cout << "\tNO." << this->Number << " Spot: " << this->Data << endl
		 << "\tAdjacent Spots: ";
	if(this->Adjacency_Vertex.size() == 0) {
		cout << "None.\n";
	}
	else {
		for(int i = 0; i < this->Adjacency_Vertex.size(); ++i) {
			cout << this->Adjacency_Vertex[i].first << "-" << this->Adjacency_Vertex[i].second << " ";
		}
		cout << endl;
	}
	cout << "\tDescription: " << this->Description << endl;
}


Edge::Edge(int subweight, string vertex1, string vertex2, bool permission) {
	this->Car_Allowed = permission;
	this->Weight = subweight;
	this->First_Vertex_Data = vertex1;
	this->Second_Vertex_Data = vertex2;
	Total_Number++;
	this->Number = Total_Number;
	this->Edge_Info = vertex1 + "-" + vertex2 + "-" + to_string(this->Weight);
	cout << "\n\tNo." << this->Number << " Path between \"" << vertex1 << "\" and \"" << vertex2 << "\" is constructed successfully.\n";
}


Edge::~Edge(){
	cout << "\n\tNo." << this->Number << " Path between \"" << this->First_Vertex_Data << "\" and \"" << this->Second_Vertex_Data << "\" is destructed successfully.\n";
	Total_Number--;
}

void Edge::Set_Weight(int target_weight) {
	this->Weight = target_weight;
}

int Edge::Get_Weight(void) const {
	return this->Weight;
}

string Edge::Get_First_Vertex_Data(void) const {
	return this->First_Vertex_Data;
}

string Edge::Get_Second_Vertex_Data(void) const {
	return this->Second_Vertex_Data;
}

void Edge::Display_Information() const {
	cout << "\tNo." << std::left << setw(3) << this->Number
		 << " Path: " << this->Edge_Info << endl
		 << "\tCar allowed: " << (this->Car_Allowed ? "Yes." : "No.") << endl;
}


string Edge::Get_Edge_Info() const {
	return this->Edge_Info;
}


Adjacency_Matrix::Adjacency_Matrix(){
	this->Total_Matrix = NULL;
	this->Size = 0;
}


Adjacency_Matrix::~Adjacency_Matrix(){
	this->Destroy_Matrix();
}


void Adjacency_Matrix::Display_Matrix() const {
	if(this->Size == 0) {
		cerr << "\n\tThere is no element in the matrix.\n";
		return;
	}
	for(int i = 0; i < this->Size; ++i){
		cout << "\t";
		for(int j = 0; j < this->Size; ++j){
			cout << std::left << setw(8) << this->Total_Matrix[i][j];
		}
		cout << "\n\n";
	}	
}


//Destroy the matrix, releasing the memory.
void Adjacency_Matrix::Destroy_Matrix(){
	for(int i = 0; i < this->Size; ++i)
		delete []this->Total_Matrix[i];
	delete []this->Total_Matrix;
}


Undirected_Graph::Undirected_Graph(){
	cerr << "\n\tUndirected graph constructed.\n";
}


Undirected_Graph::~Undirected_Graph(){
	for(int i = 0; i < this->Total_Vertex.size(); ++i){
		delete this->Total_Vertex[i];
	}
	for(int i = 0; i < this->Total_Edge.size(); ++i){
		delete this->Total_Edge[i];
	}
	cerr << "\n\tUndirected graph destructed successfully.\n";
}


//Get the number of the vertex according to the data of the vertex.
//Return the vertex if exists, and return null if not.
Vertex* Undirected_Graph::Get_Vertex_From_Data(string subdata) const{
	for(int i = 0; i < this->Total_Vertex.size(); ++i){
		if(this->Total_Vertex[i]->Data == subdata)
			return this->Total_Vertex[i];
	}
	return NULL;
}


//Get the  vertex according to the number of the vertex.
//Return the corresponding vertex if exists, and return null vertex if not.
Vertex* Undirected_Graph::Get_Vertex_From_Number(int subnumber) const{
	for(int i = 0; i < this->Total_Vertex.size(); ++i){
		if(this->Total_Vertex[i]->Number == subnumber)
			return this->Total_Vertex[i];
	}
	return NULL;
}


Edge* Undirected_Graph::Get_Edge_From_Info(string subinfo) const{
	for(int i = 0; i < this->Total_Edge.size(); ++i){
		if(this->Total_Edge[i]->Edge_Info == subinfo)
			return this->Total_Edge[i];
	}
	return NULL;
}


//Get the edge according to the input Edge_Info.
//Return Edge if exists, return null edge if not.
Edge* Undirected_Graph::Get_Edge_From_Number(int subnumber) const{
	if(subnumber > 0 && subnumber <= Edge::Total_Number)
		for(int i = 0; i < this->Total_Edge.size(); ++i){
			if(this->Total_Edge[i]->Number == subnumber)
				return this->Total_Edge[i];
		}
	return NULL;
}


//Return the pointer of the edge that connects the two input vertices.
//Return NULL if these two vertices are not connected.
Edge* Undirected_Graph::Get_Edge_From_Vertices(Vertex* vertex1, Vertex* vertex2) const {
	for(int i = 0; i < this->Total_Edge.size(); ++i) {
		//Check if the datas of the two input vertices match the datas of the two vertices in each edge.
		if(this->Total_Edge[i]->First_Vertex_Data == vertex1->Data) {
			if(this->Total_Edge[i]->Second_Vertex_Data == vertex2->Data) {
				return this->Total_Edge[i];
			}
		}
		if(this->Total_Edge[i]->First_Vertex_Data == vertex2->Data) {
			if(this->Total_Edge[i]->Second_Vertex_Data == vertex1->Data) {
				return this->Total_Edge[i];
			}
		}
	}
	return NULL;
}


//Return the pointer of the nearest vertex of the start_vertex.
//Return NULL if the start_vertex has no adjacent vertex.
Vertex* Undirected_Graph::Get_Nearest_Adjacency_Vertex(Vertex *start_vertex) const {
	if(start_vertex->Adjacency_Vertex.size() == 0)	return NULL;
	int shortest_distance = start_vertex->Adjacency_Vertex[0].second;
	string target_vertex_data(start_vertex->Adjacency_Vertex[0].first);
	for(int i = 1; i < start_vertex->Adjacency_Vertex.size(); ++i) {
		if(start_vertex->Adjacency_Vertex[i].second < shortest_distance) {
			shortest_distance = start_vertex->Adjacency_Vertex[i].second;
			target_vertex_data = start_vertex->Adjacency_Vertex[i].first;
		}
	}
	return this->Get_Vertex_From_Data(target_vertex_data);
}


//Update the information of the adjacent matrix after every change of the graph.
void Undirected_Graph::Update_Adjacency_Matrix_Info(){
	//Clear the old matrix and create the new matrix whose size is the current number of the vertices.
	//The datas in the matrix is initialized 0.
	this->Matrix.Destroy_Matrix();
	this->Matrix.Size = this->Total_Vertex.size();
	this->Matrix.Total_Matrix = new int*[this->Matrix.Size];
	for(int i = 0; i < this->Matrix.Size; ++i){
		this->Matrix.Total_Matrix[i] = new int[this->Matrix.Size];
		for(int j = 0; j < this->Matrix.Size; ++j){
			this->Matrix.Total_Matrix[i][j] = 0;
		}
	}
	//Fit in the new adjacent matrix with the weights of the edges.
	for(int i = 0; i < this->Total_Vertex.size(); ++i){	//Search the adjacent vertices from every vertex in the graph.
		for(int j = 0; j < this->Total_Vertex[i]->Adjacency_Vertex.size(); ++j){
			int k = this->Get_Vertex_From_Data(this->Total_Vertex[i]->Adjacency_Vertex[j].first)->Number - 1;	//Get the number of position that the adjacent vertex is in.
			int num = this->Total_Vertex[i]->Adjacency_Vertex[j].second;	//Get the weight of edge that connects these two vertices.
			this->Matrix.Total_Matrix[i][k] = num;	//Input the weight in the corresponding position in the adjacent matrix.
		}
	}
}


//If there is a vertex containing the same data as that in the vertex to be inserted, the targeted vertex won't be inserted, with the function returning false.
//Returning true indicates targeted vertex is inserted successfully. 
bool Undirected_Graph::Insert_Vertex(Vertex* target_vertex){
	for(int i = 0; i < this->Total_Vertex.size(); ++i){
		if(this->Total_Vertex[i]->Data == target_vertex->Data)
			return false;
	}
	this->Total_Vertex.push_back(target_vertex);
	this->Update_Adjacency_Matrix_Info(); 
	return true;
}


//If there is no vertex containing the same data as that in the parameter, the vertex required to be deleted is not in the graph. Delete failure, return false.
//Returning true indicates that targeted vertex is deleted successfully.
bool Undirected_Graph::Delete_Vertex_By_Data(string subdata){
	for(auto iter = this->Total_Vertex.begin(); iter != this->Total_Vertex.end(); ++iter){
		if((*iter)->Data == subdata){
			int subnum = (*iter)->Number;
			delete (*iter);
			this->Total_Vertex.erase(iter);	//Delete the targeted vertex.
			//Change the latter vertices' number.
			for(int i = subnum - 1; i < this->Total_Vertex.size(); ++i){
				this->Total_Vertex[i]->Number--;
			}
			//Delete the information of the deleted vertex
			for(int i = 0; i < this->Total_Vertex.size(); ++i){
				for(auto subiter = this->Total_Vertex[i]->Adjacency_Vertex.begin(); subiter != this->Total_Vertex[i]->Adjacency_Vertex.end();){
					if(subiter->first == subdata){
						subiter = this->Total_Vertex[i]->Adjacency_Vertex.erase(subiter);
					}
					else{
						++subiter;
					}
				}
			}
			for(auto subiter = this->Total_Edge.begin(); subiter != this->Total_Edge.end();){
				if((*subiter)->First_Vertex_Data == subdata || (*subiter)->Second_Vertex_Data == subdata){
					delete (*subiter);
					subiter = this->Total_Edge.erase(subiter);
				}
				else	++subiter;
			}
			this->Update_Adjacency_Matrix_Info();
			return true;
		}
	}
	return false;
}


//If the number exceeds the number of the vertices in the graph. Delete failure and return false;
//Returning true indicates that targeted vertex is deleted successfully.
bool Undirected_Graph::Delete_Vertex_By_Number(int subnumber){
	if(subnumber < 1 || subnumber > Vertex::Total_Number)
		return false;
	return this->Delete_Vertex_By_Data(this->Get_Vertex_From_Number(subnumber)->Data);
}


//More than one exact same edges connecting the same two vertices is not allowed.
//Returning true indicates that targeted edge is inserted successfully.
//Returning false indicates that the edge already exists or at least one of the vertex that the edge connects doesn't exist.
bool Undirected_Graph::Insert_Edge(Edge *target_edge){
	Vertex *subvertex = this->Get_Vertex_From_Data(target_edge->First_Vertex_Data);
	if(subvertex == NULL)	return false;
	for(int i = 0; i < subvertex->Adjacency_Vertex.size(); ++i) {
		if(subvertex->Adjacency_Vertex[i].first == target_edge->Second_Vertex_Data)
			return false;
	}
	bool first_vertex_exist = false, second_vertex_exist = false;
	for(int i = 0; i < this->Total_Vertex.size(); ++i){
		if(target_edge->First_Vertex_Data == this->Total_Vertex[i]->Data)
			first_vertex_exist = true;
		if(target_edge->Second_Vertex_Data == this->Total_Vertex[i]->Data)
			second_vertex_exist = true;
	}
	if(first_vertex_exist && second_vertex_exist) {
		this->Total_Edge.push_back(target_edge);
		this->Get_Vertex_From_Data(target_edge->First_Vertex_Data)->Adjacency_Vertex.push_back(make_pair(target_edge->Second_Vertex_Data, target_edge->Weight));
		this->Get_Vertex_From_Data(target_edge->Second_Vertex_Data)->Adjacency_Vertex.push_back(make_pair(target_edge->First_Vertex_Data, target_edge->Weight));
		this->Update_Adjacency_Matrix_Info();
		return true;
	}
	return false;
}


//If the corresponding edge doesn't exist, delete failure, returning false.
bool Undirected_Graph::Delete_Edge_By_Info(string subinfo){
	for(auto iter = this->Total_Edge.begin(); iter != this->Total_Edge.end(); ++iter){
		if((*iter)->Edge_Info == subinfo){
			int subnumber = (*iter)->Number;
			for(int i = subnumber; i < this->Total_Edge.size(); ++i){
				this->Total_Edge[i]->Number--;
			}
			Vertex *vertex1 = this->Get_Vertex_From_Data((*iter)->First_Vertex_Data);
			Vertex *vertex2 = this->Get_Vertex_From_Data((*iter)->Second_Vertex_Data);
			for(auto subiter = vertex1->Adjacency_Vertex.begin(); subiter != vertex1->Adjacency_Vertex.end(); ++subiter) {
				if(subiter->first == (*iter)->Second_Vertex_Data) {
					vertex1->Adjacency_Vertex.erase(subiter);
					break;
				}
			}
			for(auto subiter = vertex2->Adjacency_Vertex.begin(); subiter != vertex2->Adjacency_Vertex.end(); ++subiter) {
				if(subiter->first == (*iter)->First_Vertex_Data) {
					vertex2->Adjacency_Vertex.erase(subiter);
					break;
				}
			}
			delete (*iter);
			this->Total_Edge.erase(iter);
			this->Update_Adjacency_Matrix_Info();
			return true;
		}
	}
	return false;
}


//If the input number exceeds the legal range, delete failure, returning false.
bool Undirected_Graph::Delete_Edge_By_Number(int subnumber){
	if(subnumber < 1 || subnumber > Edge::Total_Number)
		return false;
	return this->Delete_Edge_By_Info(this->Get_Edge_From_Number(subnumber)->Edge_Info);
}


//Need imporving
void Undirected_Graph::Display_Adjacency_Matrix() const{
	cout << "\n\tThe adjacent matrix is as follows:\n\n\t\t\t";
	for(int i = 0; i < this->Total_Vertex.size(); ++i) {
		cout << std::left << setw(16) << this->Total_Vertex[i]->Data;
	}
	cout << endl;
	for(int i = 0; i < this->Total_Vertex.size(); ++i) {
		cout << std::right << setw(16) << this->Total_Vertex[i]->Data << "\t";
		for(int j = 0; j < this->Matrix.Size; ++j) {
			cout << std::left << setw(16) << this->Matrix.Total_Matrix[i][j];
		}
		cout << endl;
	}
}


//Output all the adjacent vertices of every vertex in the graph.
void Undirected_Graph::Display_All_Vertices() const {
	if(this->Total_Vertex.size() == 0) {
		cerr << "\n\tThere is no spot in the map.\n";
		return;
	}
	cout << "\n\tThe information of all the spots in the map are as follows:\n\n";
	cout << "\t---------------------------------------------\n";
	for(int i = 0; i < this->Total_Vertex.size(); ++i){
		this->Total_Vertex[i]->Display_Information();
		cout << "\t---------------------------------------------\n";
	} 
}


void Undirected_Graph::Display_All_Edges() const {
	if(this->Total_Edge.size() == 0) {
		cerr << "\n\tThere is no path in the map.\n";
		return;
	}
	cout << "\n\tThe information of all the paths in the map are as follows:\n\n";
	cout << "\t-----------------------------------\n";
	for(int i = 0; i < this->Total_Edge.size(); ++i) {
		this->Total_Edge[i]->Display_Information();
		cout << "\t-----------------------------------\n";
	}
}


//Return the shortest path between the begin_vertex and second_vertex in the form of vector<Vertex*>;
//If the two vertices are not connected, the function returns Null_Path which contains no pointer of the vertex;
//The result_sum in the parameter list indicates the shortest distance between these two vertices;
//If onfoot parameter is false, that means that the shortest path must be able to be passed by cars;
vector<Vertex*> Undirected_Graph::Get_Shortest_Route(Vertex *begin_vertex, Vertex *end_vertex, int &result_sum, bool onfoot) const {
	vector<Vertex*> Finding_Path, Result_Path, Null_Path;
	int Finding_Distance = 0, Result_Distance = INF;
	bool *visited = new bool[this->Total_Vertex.size()];
	for(int i = 0; i < this->Total_Vertex.size(); ++i) {
		visited[i] = false;
	}
	//The lambda expression to find out the shortest path recursively;
	function<void(Vertex*, Vertex*)> Find;
	Find = [&](Vertex *begin, Vertex *end) {	
		if(begin == end) {
			if(Finding_Distance < Result_Distance) {
				Result_Path.clear();
				for(int i = 0; i < Finding_Path.size(); ++i)
					Result_Path.push_back(Finding_Path[i]);
				Result_Distance = Finding_Distance;
			}
		}
		Vertex *subbegin = NULL;
		for(int i = 0; i < begin->Adjacency_Vertex.size(); ++i) {
			subbegin = this->Get_Vertex_From_Data(begin->Adjacency_Vertex[i].first);
			if(visited[subbegin->Number - 1] == true)	continue;
			if(onfoot == false) {
				if(this->Get_Edge_From_Vertices(subbegin, begin)->Car_Allowed == false)	continue;
			}
			visited[subbegin->Number - 1] = true;
			Finding_Path.push_back(subbegin);
			Finding_Distance += begin->Adjacency_Vertex[i].second;
			Find(subbegin, end);
			visited[subbegin->Number - 1] = false;
			Finding_Path.pop_back();
			Finding_Distance -= begin->Adjacency_Vertex[i].second;
		}
	};
	Find(begin_vertex, end_vertex);
	delete []visited;
	if(Result_Distance == INF)	return Null_Path;
	result_sum = Result_Distance;
	return Result_Path;
}











Service* Service::get_instance() {
	static Service total_service;
	return &total_service;
}

template <typename T>
bool Service::input_judge(T &data) {
	if(!(cin >> data)) {
		cerr << "\n\tIllegal input.\n";
		cin.clear();
		cin.sync();
		return false;
	}
	return true;
}

bool Service::Password_Authentication() const {
	int input_chance = 3;
	string my_password;
	while(input_chance != 0) {
		cout << "\n\tPlease input the password: ";
		getline(cin, my_password);
		if(my_password != this->password) {
			cerr << "\n\tIncorrect password.\n";
			if(--input_chance != 0) {
				cerr << "\tYou have " << input_chance << " more " << (input_chance == 1 ? "chance." : "chances.") << endl;
			}
			else {
				cerr << "\tProgram entered failure.\n";
			}
		}
		else {
			cerr << "\n\tCorrect password. Program entered successfully.\n";
			return true;
		}
	}
	return false;
}

void Service::Output_Function() const {
	cout << "\n\n\tInput the number to execute the corresponding function below:\n"
		 << "\t---------------------------------------------------\n"
		 << "\t0                                   Clear The Sreen\n"
		 << "\t---------------------------------------------------\n"
		 << "\t1                                       Insert Spot\n"
		 << "\t---------------------------------------------------\n"
		 << "\t2                                       Insert Path\n"
		 << "\t---------------------------------------------------\n"
		 << "\t3                                       Delete Spot\n"
		 << "\t---------------------------------------------------\n"
		 << "\t4                                       Delete Path\n"
		 << "\t---------------------------------------------------\n"
		 << "\t5                              Show Adjacent Matrix\n"
		 << "\t---------------------------------------------------\n"
		 << "\t6                            Show Spots Information\n"
		 << "\t---------------------------------------------------\n"
		 << "\t7                            Show Paths Information\n"
		 << "\t---------------------------------------------------\n"
		 << "\t8                                Get Shortest Route\n"
		 << "\t---------------------------------------------------\n"
		 << "\t9                                  Exit The Program\n"
		 << "\t---------------------------------------------------\n"
		 << "\tPlease input the number: ";
}

void Service::Ouput_Dash(int num) const {
	cout << "\t";
	for(int i = 0; i < num; ++i) {
		cout << "-";
	}
	cout << endl;
}

void Service::Insert_Vertex() {
	string vertex_data, vertex_des;
	cout << "\n\tInput the name of the spot: ";
	getline(cin, vertex_data);
	cout << "\n\tInput the description of the spot below:\n";
	getline(cin, vertex_des);
	Vertex *target_vertex = new Vertex(vertex_data, vertex_des);
	if(this->My_Graph.Insert_Vertex(target_vertex)) {
		cout << "\n\tSpot \"" << vertex_data << "\" is inserted successfully.\n";
	}
	else {
		cerr << "\n\tSpot \"" << vertex_data << "\" already exists in the map. Insert failure.\n";
		delete target_vertex;
	}
}

void Service::Insert_Edge() {
	string vertex1, vertex2, onfoot_judge;
	int edge_weight = 0;
	bool onfoot = false;
	cout << "\n\tInput the length of the path: ";
	if(!this->input_judge(edge_weight)) {
		cerr << "\tPath insert failure.\n";
		return;
	}
	cin.clear();
	cin.sync();
	cout << "\n\tInput the names of the two spots that the path connects below.\n"
		 << "\n\tThe name of the first spot: ";
	getline(cin, vertex1);
	cout << "\n\tThe name of the second spot: ";
	getline(cin, vertex2);
	cout << "\n\tIs this path allowed to be passed by cars? (y/n): ";
	getline(cin, onfoot_judge);
	if(onfoot_judge.size() > 1) {
		cerr << "\n\tIllegal input. Program terminated automatically.\n";
		return;
	}
	else if(onfoot_judge[0] == 'y' || onfoot_judge[0] == 'Y')	onfoot = true;
	else if(onfoot_judge[0] == 'n' || onfoot_judge[0] == 'N')	onfoot = false;
	else {
		cerr << "\n\tNot recognized. Program terminated automatically.\n";
		return;
	}
	Edge *target_edge = new Edge(edge_weight, vertex1, vertex2, onfoot);
	if(this->My_Graph.Insert_Edge(target_edge)) {
		cout << "\n\tThe spot is inserted successfully.\n";
	}
	else {
		cerr << "\n\tThe spot is inserted unsuccessfully.\n"
			 << "\tMaybe some of the spot doesn't exist, or there is already a path connecting these two spots.\n";
		delete target_edge;
	}
}

void Service::Delete_Vertex() {
	string vertex_data;
	cout << "\n\tInput the name of the spot that needs deleting: ";
	getline(cin, vertex_data);
	if(this->My_Graph.Delete_Vertex_By_Data(vertex_data)) {
		cout << "\n\tSpot \"" << vertex_data << "\" is deleted successfully.\n";
	}
	else {
		cerr << "\n\tSpot \"" << vertex_data << "\" doesn't exist in the graph."
			 << "\n\tSpot deleted unsuccessfully.\n";
	}
}

void Service::Delete_Edge() {
	int edge_number = 0;
	this->Output_All_Edges();
	cout << "\n\tInput the number of the path that you want to delete: ";
	if(!this->input_judge(edge_number)) {
		cerr << "\tProgram terminated automatically.\n";
		return;
	}
	cin.clear();
	cin.sync();
	Edge *subptr = this->My_Graph.Get_Edge_From_Number(edge_number);
	string deleted_edge_info;
	if(subptr != NULL)
		deleted_edge_info = subptr->Get_Edge_Info();
	if(this->My_Graph.Delete_Edge_By_Number(edge_number)) {
		cout << "\n\tPath: " << deleted_edge_info << " is deleted successfully.\n";
	}
	else {
		cerr << "\n\tIllegal number. Path deleted failure.\n";
	}
}

void Service::Output_Adjacency_Matrix() {
	this->My_Graph.Display_Adjacency_Matrix();
}

void Service::Output_All_Vertices() {
	this->My_Graph.Display_All_Vertices();
}

void Service::Output_All_Edges() {
	this->My_Graph.Display_All_Edges();
}

void Service::Shortest_Route() {
	string begin_data, end_data, onfoot_choice;
	bool onfoot = false;
	int shortest_distance = 0;
	Vertex *begin = NULL, *end = NULL;
	cout << "\n\tPlease input the name of the starting spot: ";
	getline(cin, begin_data);
	begin = this->My_Graph.Get_Vertex_From_Data(begin_data);
	if(begin == NULL) {
		cerr << "\n\tThere is no such spot on the map. Program terminated automatically.\n";
		return;
	}
	cout << "\n\tPlease input the name of the ending spot: ";
	getline(cin, end_data);
	end = this->My_Graph.Get_Vertex_From_Data(end_data);
	if(end == NULL) {
		cerr << "\n\tThere is no such spot on the map. Program terminated automatically.\n";
		return;
	}
	cout << "\n\tTravel by car or on foot? (y/n) ('y' means by car, 'n' means on foot): ";
	getline(cin, onfoot_choice);
	if(onfoot_choice.size() > 1) {
		cerr << "\n\tIllegal input. Program terminated automatically.\n";
		return;
	}
	if(onfoot_choice[0] == 'y' || onfoot_choice[0] == 'Y')	onfoot = false;
	else if(onfoot_choice[0] == 'n' || onfoot_choice[0] == 'N')	onfoot = true;
	else {
		cerr << "\n\tNot recognized. Program terminated automatically.\n";
		return;
	}
	vector<Vertex*> result(this->My_Graph.Get_Shortest_Route(begin, end, shortest_distance, onfoot));
	if(result.size() == 0) {
		cout << "\n\tThere is no matching path between \"" << begin->Get_Data() << "\" and \"" << end->Get_Data() << "\".\n";
	}
	else {
		cout << "\n\t" << begin->Get_Data();
		for(int i = 0; i < result.size(); ++i) {
			cout << " -> " << result[i]->Get_Data();
		}
		cout << "\n\tThe shortest distance between \"" << begin->Get_Data() << "\" and \"" << end->Get_Data() << "\" is " << shortest_distance << endl;
	}
}

bool Service::Exit_Judge_Function() {
	string input_judge;
	cout << "\n\tDo you want to exit the program? (y/n): ";
	getline(cin, input_judge);
	if(input_judge.size() > 1) {
		cerr << "\n\tIllegal input. Program returned automatically.\n";
		return false;
	}
	else if(input_judge[0] == 'y' || input_judge[0] == 'Y') {
		cerr << "\n\tCommand accepted. Program ended successfully.\n";
		return true;
	}
	else {
		cerr << "\n\tNot recognized. Program returned automatically.\n";
		return false;
	}
}






int main(void)
{
	system("color f0");
	static Service *total_service = Service::get_instance();
	if(!total_service->Password_Authentication())	return 0;
	string input_choice;
	bool exit_program = false;
	while(!exit_program) {
		total_service->Output_Function();
		getline(cin, input_choice);
		if(input_choice.size() > 1) {
			cerr << "\n\tIllegal input.\n";
			continue;
		}
		switch(input_choice[0]) {
			case '0':
				system("cls");
				break;
			case '1':
				total_service->Insert_Vertex();
				break;
			case '2':
				total_service->Insert_Edge();
				break;
			case '3':
				total_service->Delete_Vertex();
				break;
			case '4':
				total_service->Delete_Edge();
				break;
			case '5':
				total_service->Output_Adjacency_Matrix();
				break;
			case '6':
				total_service->Output_All_Vertices();
				break;
			case '7':
				total_service->Output_All_Edges();
				break;
			case '8':
				total_service->Shortest_Route();
				break;
			case '9':
				exit_program = total_service->Exit_Judge_Function();
				break;
			default:
				cerr << "\n\tNot recognized.\n";
				break;
		}
	}
	cout << "\n\tProgram terminated successfully.\n";
	return 0;





////Test code
//	system("color f0");
//	cout << "\n\tMain Function Begins.\n";
//
//	Vertex *v1 = new Vertex("mingde", "The mingdeyuan in the Sun Yat-sen University");
//	Vertex *v2 = new Vertex("zhishan", "The zhishanyuan in the SYSU");
//	Vertex *v3 = new Vertex("GOGO", "The commercial center in the Higher Educational Mega Center");
//	Vertex *v4 = new Vertex("shensi", "The shensiyuan of SYSU");
//	Vertex *v5 = new Vertex("Lab", "The laboratory in the north area");
//	Vertex *v6 = new Vertex("Pool", "Swimming pool");
//	Vertex *v7 = new Vertex("PlayGround", "Two different playgrounds in the SYSU");
////	Vertex *v8 = new Vertex("TeachBuild", "The teaching building in the SYSU");
//	
//	Edge *e1 = new Edge(40, "mingde", "zhishan");
//	Edge *e2 = new Edge(30, "mingde", "GOGO");
//	Edge *e3 = new Edge(70, "mingde", "shensi");
//	Edge *e4 = new Edge(24, "zhishan", "Lab");
//	Edge *e5 = new Edge(30, "GOGO", "Lab");
//	Edge *e6 = new Edge(5, "GOGO", "zhishan");
//	Edge *e7 = new Edge(40, "Lab", "shensi");
//	Edge *e8 = new Edge(30, "PlayGround", "Pool");
//	Edge *e9 = new Edge(16, "mingde", "Pool");
//	Edge *e10 = new Edge(28, "mingde", "Dorm");
//	Edge *e11 = new Edge(89, "GOGO", "PlayGround");
//	Edge *e12 = new Edge(37, "PlayGround", "Lab");
////	Edge *e13 = new Edge(60, "Dorm", "TeachBuild");
////	Edge *e14 = new Edge(40, "TeachBuild", "Gym");
//
//	Undirected_Graph my_graph;
//	
//	if(my_graph.Insert_Vertex(v1))	cout << "\tV1 \"first\" is inserted successfully.\n";
//	else	cout << "\tV1 \"first\" is inserted failure.\n";
//	if(my_graph.Insert_Vertex(v2))	cout << "\tV2 \"second\" is inserted successfully.\n";
//	else	cout << "\tV2 \"second\" is inserted failure.\n";
//	if(my_graph.Insert_Vertex(v3))	cout << "\tV3 \"third\" is inserted successfully.\n";
//	else	cout << "\tV3 \"third\" is inserted failure.\n";
//	if(my_graph.Insert_Vertex(v4))	cout << "\tV4 \"forth\" is inserted successfully.\n";
//	else	cout << "\tV4 \"forth\" is inserted failure.\n";
//	if(my_graph.Insert_Vertex(v5))	cout << "\tV5 \"fifth\" is inserted successfully.\n";
//	else	cout << "\tV5 \"fifth\" is inserted failure.\n";
//	if(my_graph.Insert_Vertex(v6))	cout << "\tV6 \"fifth\" is inserted successfully.\n";
//	else	cout << "\tV5 \"fifth\" is inserted failure.\n";
//	if(my_graph.Insert_Vertex(v7))	cout << "\tV5 \"fifth\" is inserted successfully.\n";
//	else	cout << "\tV5 \"fifth\" is inserted failure.\n";
//	
//	if(my_graph.Insert_Edge(e1))	cout << "\tEdge 1 is inserted successfully.\n";
//	else	cout << "\tEdge 1 inserted failure.\n";
//	if(my_graph.Insert_Edge(e2))	cout << "\tEdge 2 is inserted successfully.\n";
//	else	cout << "\tEdge 2 inserted failure.\n";
//	if(my_graph.Insert_Edge(e3))	cout << "\tEdge 3 is inserted successfully.\n";
//	else	cout << "\tEdge 3 inserted failure.\n";
//	if(my_graph.Insert_Edge(e4))	cout << "\tEdge 4 is inserted successfully.\n";
//	else	cout << "\tEdge 4 inserted failure.\n";
//	if(my_graph.Insert_Edge(e5))	cout << "\tEdge 5 is inserted successfully.\n";
//	else	cout << "\tEdge 5 inserted failure.\n";
//	if(my_graph.Insert_Edge(e6))	cout << "\tEdge 6 is inserted successfully.\n";
//	else	cout << "\tEdge 6 inserted failure.\n";	
//	if(my_graph.Insert_Edge(e7))	cout << "\tEdge 7 is inserted successfully.\n";
//	else	cout << "\tEdge 7 inserted failure.\n";
//	if(my_graph.Insert_Edge(e8))	cout << "\tEdge 7 is inserted successfully.\n";
//	else	cout << "\tEdge 7 inserted failure.\n";	
//	if(my_graph.Insert_Edge(e9))	cout << "\tEdge 7 is inserted successfully.\n";
//	else	cout << "\tEdge 7 inserted failure.\n";	
//	if(my_graph.Insert_Edge(e10))	cout << "\tEdge 7 is inserted successfully.\n";
//	else	cout << "\tEdge 7 inserted failure.\n";	
//	if(my_graph.Insert_Edge(e11))	cout << "\tEdge 7 is inserted successfully.\n";
//	else	cout << "\tEdge 7 inserted failure.\n";	
//	if(my_graph.Insert_Edge(e12))	cout << "\tEdge 7 is inserted successfully.\n";
//	else	cout << "\tEdge 7 inserted failure.\n";	
//	
//
//	my_graph.Display_Adjacency_Matrix();
//	my_graph.Display_All_Vertices();
//	my_graph.Display_All_Edges();
//	
//	int sum = 0;
//	vector<Vertex*> sub = my_graph.Get_Shortest_Route(v1, v5, sum, false);
//	if(sub.size() == 0)	cout << "\n\tNo matching path.\n";
//	else {
//		cout << "\n\t" << v1->Get_Data();
//		for(int i = 0; i < sub.size(); ++i) {
//			cout << " -> " << sub[i]->Get_Data();
//		}
//		cout << "\n\tThe shortest distance: " << sum << endl;
//	}
//	
//	cout << "\n\tMain Function Ends.\n";
//	return 0;
}
