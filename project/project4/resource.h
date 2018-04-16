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
		string Data;	//�ý���ڴ洢����Ϣ 
		int Number;	//�ý��ı�� 
		string Description; 
		vector<pair<string, int> > Adjacency_Vertex;	//��¼�ýڵ����ڽ�����Ϣ 
		static int Total_Number;	//��¼һ���ж��ٸ���� 
		
	public:
		friend class Undirected_Graph; 
		
	public:
		Vertex(string = "NULL", string = "NULL");	//���캯��
		~Vertex();	//�������� 
		void Set_Data(string);	//�������øý�����Ϣ 
		string Get_Data(void) const;	//���ظý����Ϣ 
		void Set_Description(string);	//���ý�������Ϣ 
		string Get_Description(void) const;	//���ؾ�����Ϣ 
		int Get_Number(void) const;	//���ظý���� 
		void Display_Information() const;	//����ý�����ϸ��Ϣ 
		bool Is_Adjacent(string) const;	//�жϲ�������Ϣ��Ӧ�Ľ���Ƿ���ý������ 
		
};


class Edge{
	
	private:
		int Weight;	//�ߵ�Ȩ�أ�Ҳ��·���ĳ��� 
		string First_Vertex_Data, Second_Vertex_Data;	//��¼��·�����ӵ������������� 
		string Edge_Info;	//��¼·���ڴ洢�ľ�����Ϣ 
		bool Car_Allowed;	//�жϸ�·���Ƿ�������ͨ�� 
		int Number;	//��·���ı�� 
		static int Total_Number;	//�����·�������� 
		
	public:
		friend class Undirected_Graph; 
		
	public:	
		Edge(int = 0, string = "NULL", string = "NULL", bool = true);	//���캯�� 
		~Edge();	//�������� 
		void Set_Weight(int);	//����·���ĳ��� 
		int Get_Weight(void) const;	//����·���ĳ��� 
		string Get_Edge_Info() const;	//����·������ϸ��Ϣ 
		string Get_First_Vertex_Data(void) const;	//���ظ�·�����ӵ���������е�һ���������� 
		string Get_Second_Vertex_Data(void) const;	//���ظ�·�����ӵ���������еڶ����������� 
		void Display_Information() const;	//�����·������ϸ��Ϣ 

};


class Adjacency_Matrix{	

	private:
		int **Total_Matrix;
		int Size; 
		
	public:
		friend class Undirected_Graph; 
		
	public:
		Adjacency_Matrix();	//���캯�� 
		~Adjacency_Matrix();	//�������� 
		void Display_Matrix() const;	//����ڽӾ��� 
		void Destroy_Matrix();	//�ͷ��ڽӾ�����������ڴ�ռ� 

};


class Undirected_Graph{
	private:
		vector<Vertex*> Total_Vertex;	//��¼������ͼ�����еĽ�� 
		vector<Edge*> Total_Edge;	//��¼������ͼ�����е�·�� 
		Adjacency_Matrix Matrix;	//�ڽӾ���	
	public:
		Undirected_Graph();	//����ͼ���캯�� 
		~Undirected_Graph();	//����ͼ�������� 
		Vertex* Get_Vertex_From_Data(string) const;	//�������ַ��ؽ���ָ�룬����ΪĿ��������� 
		Vertex* Get_Vertex_From_Number(int) const;	//���ݱ�ŷ��ؽ���ָ�룬����ΪĿ����ı�� 
		Edge* Get_Edge_From_Info(string) const;	//������Ϣ����·����ָ�룬����ΪĿ��·������Ϣ 
		Edge* Get_Edge_From_Number(int) const;	//���ݱ�ŷ���·����ָ�룬����ΪĿ��·���ı�� 
		Edge* Get_Edge_From_Vertices(Vertex*, Vertex*) const;	//����������㷵�����Ӹ���������·��ָ�� 
		Vertex* Get_Nearest_Adjacency_Vertex(Vertex*) const;	//���ؾ�������н������Ľ��ָ�� 
		void Update_Adjacency_Matrix_Info();	//��������ͼ�ڲ������·���ı仯�����ڽӾ������Ϣ 
		bool Insert_Vertex(Vertex*);	//���������ָ�����ͼ�У�������ͬ�������� 
		bool Delete_Vertex_By_Data(string);	//���ݽ�������ɾ��ͼ�ڵĽ�㣬����ΪĿ��������� 
		bool Delete_Vertex_By_Number(int);	//���ݽ��ı��ɾ��ͼ�ڵĽ�㣬����ΪĿ����ı�� 
		bool Insert_Edge(Edge*);	//�������ڵ�·������ͼ�У����������·��������ͬ������� 
		bool Delete_Edge_By_Info(string);	//����·������ϸ��Ϣɾ��·��������ΪĿ��·������Ϣ 
		bool Delete_Edge_By_Number(int);	///����·���ı��ɾ��·��������ΪĿ��·���ı�� 
		void Display_Adjacency_Matrix() const;	//����ڽӾ��� 
		void Display_All_Vertices() const;	//���ͼ�����н�����ϸ��Ϣ 
		void Display_All_Edges() const;		//���ͼ������·������ϸ��Ϣ 
		vector<Vertex*> Get_Shortest_Route(Vertex*, Vertex*, int&, bool) const;	//Ѱ�Ҳ����������֮������·�� 
};


class Service{
	private:
		Service() {};
		const string password = "sapphire";
		Undirected_Graph My_Graph;
	public:
		~Service() = default;
		static Service* get_instance();	//����ģʽ���� 
		template <typename T> 
		bool input_judge(T&);
		bool Password_Authentication() const;	//����������� 
		void Ouput_Dash(int) const;
		void Output_Function() const;	//������˵� 
		void Insert_Vertex();	//���뾰�� 
		void Insert_Edge();	//����·�� 
		void Delete_Vertex();	//ɾ������ 
		void Delete_Edge();	//ɾ��·�� 
		void Output_Adjacency_Matrix();	//����ڽӾ��� 
		void Output_All_Vertices();	//������о������ϸ��Ϣ 
		void Output_All_Edges();	//�������·������ϸ��Ϣ 
		void Shortest_Route();	//Ѱ����������֮������·�� 
		bool Exit_Judge_Function();	//�ж��Ƿ���ֹ���� 
};


#endif
