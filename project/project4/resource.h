#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <windows.h>
using namespace std;


class Vertex;
class Edge;
class Adjacency_Matrix;
class Undirected_Graph;


class Vertex{
	
	private:
		string Data;	//该结点内存储的信息 
		int Number;	//该结点的编号 
		string Description; 
		vector<pair<string, int> > Adjacency_Vertex;	//记录该节点相邻结点的信息 
		static int Total_Number;	//记录一共有多少个结点 
		
	public:
		friend class Undirected_Graph; 
		
	public:
		Vertex(string = "NULL", string = "NULL");	//构造函数
		~Vertex();	//析构函数 
		void Set_Data(string);	//重新设置该结点的信息 
		string Get_Data(void) const;	//返回该结点信息 
		void Set_Description(string);	//重置结点具体信息 
		string Get_Description(void) const;	//返回具体信息 
		int Get_Number(void) const;	//返回该结点编号 
		void Display_Information() const;	//输出该结点的详细信息 
		bool Is_Adjacent(string) const;	//判断参数内信息对应的结点是否与该结点相邻 
		
};


class Edge{
	
	private:
		int Weight;	//边的权重，也是路径的长度 
		string First_Vertex_Data, Second_Vertex_Data;	//记录该路径连接的两个结点的名字 
		string Edge_Info;	//记录路径内存储的具体信息 
		bool Car_Allowed;	//判断该路径是否允许车辆通过 
		int Number;	//该路径的编号 
		static int Total_Number;	//创造的路径的总数 
		
	public:
		friend class Undirected_Graph; 
		
	public:	
		Edge(int = 0, string = "NULL", string = "NULL", bool = true);	//构造函数 
		~Edge();	//析构函数 
		void Set_Weight(int);	//重置路径的长度 
		int Get_Weight(void) const;	//返回路径的长度 
		string Get_Edge_Info() const;	//返回路径的详细信息 
		string Get_First_Vertex_Data(void) const;	//返回该路径连接的两个结点中第一个结点的名字 
		string Get_Second_Vertex_Data(void) const;	//返回该路径连接的两个结点中第二个结点的名字 
		void Display_Information() const;	//输出该路径的详细信息 

};


class Adjacency_Matrix{	

	private:
		int **Total_Matrix;
		int Size; 
		
	public:
		friend class Undirected_Graph; 
		
	public:
		Adjacency_Matrix();	//构造函数 
		~Adjacency_Matrix();	//析构函数 
		void Display_Matrix() const;	//输出邻接矩阵 
		void Destroy_Matrix();	//释放邻接矩阵所申请的内存空间 

};


class Undirected_Graph{
	private:
		vector<Vertex*> Total_Vertex;	//记录该无向图中所有的结点 
		vector<Edge*> Total_Edge;	//记录该无向图中所有的路径 
		Adjacency_Matrix Matrix;	//邻接矩阵	
	public:
		Undirected_Graph();	//无向图构造函数 
		~Undirected_Graph();	//无向图析构函数 
		Vertex* Get_Vertex_From_Data(string) const;	//根据名字返回结点的指针，参数为目标结点的名字 
		Vertex* Get_Vertex_From_Number(int) const;	//根据编号返回结点的指针，参数为目标结点的编号 
		Edge* Get_Edge_From_Info(string) const;	//根据信息返回路径的指针，参数为目标路径的信息 
		Edge* Get_Edge_From_Number(int) const;	//根据编号返回路径的指针，参数为目标路径的编号 
		Edge* Get_Edge_From_Vertices(Vertex*, Vertex*) const;	//根据两个结点返回连接该两个结点的路径指针 
		Vertex* Get_Nearest_Adjacency_Vertex(Vertex*) const;	//返回距离参数中结点最近的结点指针 
		void Update_Adjacency_Matrix_Info();	//根据无向图内部结点与路径的变化更新邻接矩阵的信息 
		bool Insert_Vertex(Vertex*);	//将参数结点指针插入图中，不允许同名结点存在 
		bool Delete_Vertex_By_Data(string);	//根据结点的名称删除图内的结点，参数为目标结点的名称 
		bool Delete_Vertex_By_Number(int);	//根据结点的编号删除图内的结点，参数为目标结点的编号 
		bool Insert_Edge(Edge*);	//将参数内的路径插入图中，不允许多条路径连接相同两个结点 
		bool Delete_Edge_By_Info(string);	//根据路径的详细信息删除路径，参数为目标路径的信息 
		bool Delete_Edge_By_Number(int);	///根据路径的编号删除路径，参数为目标路径的编号 
		void Display_Adjacency_Matrix() const;	//输出邻接矩阵 
		void Display_All_Vertices() const;	//输出图内所有结点的详细信息 
		void Display_All_Edges() const;		//输出图内所有路径的详细信息 
		vector<Vertex*> Get_Shortest_Route(Vertex*, Vertex*, int&, bool) const;	//寻找参数两个结点之间的最短路径 
};


class Service{
	private:
		Service() {};
		const string password = "sapphire";
		Undirected_Graph My_Graph;
	public:
		~Service() = default;
		static Service* get_instance();	//单例模式函数 
		template <typename T> 
		bool input_judge(T&);
		bool Password_Authentication() const;	//密码解锁函数 
		void Ouput_Dash(int) const;
		void Output_Function() const;	//输出主菜单 
		void Insert_Vertex();	//插入景点 
		void Insert_Edge();	//插入路径 
		void Delete_Vertex();	//删除景点 
		void Delete_Edge();	//删除路径 
		void Output_Adjacency_Matrix();	//输出邻接矩阵 
		void Output_All_Vertices();	//输出所有景点的详细信息 
		void Output_All_Edges();	//输出所有路径的详细信息 
		void Shortest_Route();	//寻找两个景点之间的最短路径 
		bool Exit_Judge_Function();	//判断是否终止程序 
};


#endif
