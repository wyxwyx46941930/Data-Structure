
#include "Plane.h"
#include "Runway.h"
#include "Extended_Queue.h"
#include "Random.h"
#include <iostream>
#include <string>
#include <windows.h>

PAINTSTRUCT paint;
HDC hDC;
RECT rect;
//�ص�����
LRESULT WINAPI WinProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
    switch(Msg)//������Ϣ���̣�ʲô����Ϣ���½��ٽ�
    {
	case WM_PAINT:
		//BginPaint��Щ�滭�Ŀ�ʼ���������PAINSTURCT�ṹ�������豸�����ģ���ʱ������⣩���
		hDC=BeginPaint(hWnd,&paint);
		//GetClientRect������ȡ�������ڿͻ�����λ�ô�С��Ϣ
		GetClientRect(hWnd,&rect);
		//DrawText����Windows����"����"�ı��ˣ�DT_*֮����ָ���ֵ���ʽ����������˼Ҳ�ܿ�����
		//�ж�����ʽ�أ����Բ鿴����http://msdn.microsoft.com/en-us/library/ms901121.aspx
		//�������ǵ��ߡ�ˮƽ���к���ֱ���С�
		DrawText(hDC,"P6�������ȳ�����ɣ�����out.txt�в鿴���",-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		//EndPaint������Щ��β�Ĺ����ˡ�
		EndPaint(hWnd,&paint);
		break;
    case WM_DESTROY://��Ӧ��굥���رհ�ť�¼�
        PostQuitMessage(0);//�˳���Ϣ���У�����ʲô����Ϣ���У��½�˵
        return 0;//�˳�����
    }
    return DefWindowProc(hWnd,Msg,wParam,lParam);
}


using namespace std;

extern int crashes;

void initialize(int &end_time, int &queue_limit,
                double &arrival_rate, double &departure_rate)
/*Pre: The user specifies the number of timeunits in the simulation,the maximal queue sizes permitted, and the expected arrival and departure rates for the airport.
 Post: The program prints instructions and initializes the parameters end_time, queue_limit, arrival_rate, and departure_rate to the specified values.
 Uses: utility function user_says_yes*/
{   
    crashes=0;
     cout <<"This program simulates an airport with only one runway."<<endl <<"One plane can land or depart in each unit of time."<<endl;
     cout <<"Up to what number of planes can be waiting to land " <<"or take off at any time?"<<flush;
     cin >>queue_limit;
     cout <<"How many units of time will the simulation run?"<<flush; cin >>end_time;
    bool acceptable=false;
     do{
         cout <<"Expected number of arrivals per unit time?"<<flush;
         cin >>arrival_rate;
         cout <<"Expected number of departures per unit time?"<<flush;
         cin >>departure_rate;
         if (arrival_rate<0.0||departure_rate<0.0) cerr<<"These rates must be nonnegative."<<endl;
         else
             acceptable = true;
         if (acceptable&&arrival_rate + departure_rate>1.0)
             cerr << "Safety Warning: This airport will become saturated." <<endl;
     }while (!acceptable);
}


void run_idle(int time)
/*Post: The specified time is printed with a message that the runway isidle.*/ {
    cout <<time<<": Runway isidle."<<endl;
}





int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd) {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    // Airport simulation program
    /*Pre: The user must supply the number of time intervals the simulation isto run, the expected number of planes arriving, the expected number of planes departing per time interval, and the maximum allowed size for runway
     queues.
     Post: The program performs a random simulation of the airport, showing the
     status of the runway at each time interval, and prints out a summary of
     airport operation at the conclusion.
     Uses: Classes Runway, Plane, Random and functionsrun_idle, initialize.*/
    int end_time; // time to run simulation
    int queue_limit; // size of Runway queues
    int flight_number = 0;
    double arrival_rate,departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    
    Random variable;
    bool emergency_action;
    Plane moving_plane;
    Runway small_airport(queue_limit);
    for (int current_time = 0; current_time<end_time;current_time++){
            // loop over time intervals
        emergency_action=false;
        int number_arrivals = variable.poisson(arrival_rate);
            // current arrival requests
        for(int i=0; i<number_arrivals; i++){
            Plane current_plane(flight_number++, current_time, arriving);
            if (!emergency_action && current_plane.get_status() == emergency) { 
                cout << "EMERGENCY normal action suspended at airport " << endl; 
                emergency_action = true;  
                moving_plane = current_plane; // it can land at once 
            } 
            else if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
        
        }
        int number_departures = variable.poisson(departure_rate);
        // current departure requests
        for(int j=0; j<number_departures; j++){
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }
        if (emergency_action) 
            moving_plane.land(current_time);
        switch (small_airport.activity(current_time, moving_plane)){
                // Let at most one Plane onto the Runway at current_time.
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff1:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
        }
    }
    cout << "\n\n------------ Runway Statistics ---------------\n" << endl; 
    small_airport.shut_down(end_time);  
    cout << "\n\n-------------------------------------------\n" << endl;  
    cout << "The airport allowed " << crashes << " planes to crash." << endl;
    char *cName = "myWindow";
    WNDCLASSEX wc;
    HWND hWnd;
    MSG Msg;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL);//ͨ������������һ����ɫ�ı���������������ΪNULL�����������Ȥ��
    wc.hCursor = NULL;//������
    wc.hIcon = NULL;//������
    wc.hIconSm = NULL;//������
    wc.hInstance = hInstance;//��ǰ����ľ����hInstance����ϵͳ�����ݵ�
    wc.lpfnWndProc = WinProc;//���ڴ�����̵Ļص�������
    wc.lpszClassName =(LPSTR)cName;//����������֡�
    wc.lpszMenuName = NULL;//Ŀ¼����������
    wc.style = CS_HREDRAW | CS_VREDRAW; 

    RegisterClassEx(&wc);//��ϵͳ��ע��

    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,cName,"P6�汾",WS_OVERLAPPEDWINDOW,
        200,100,600,400,NULL,NULL,hInstance,NULL);//�������ڣ����ڱ���Ϊ"�ҵĴ�����ϲ��"
    if(hWnd == NULL)
    {//�ݴ���
        MessageBox(NULL,"There's an Error","Error Title",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }
    ShowWindow(hWnd,nShowCmd);//��ʾ����
    UpdateWindow(hWnd);

    //�����Ƕ���Ϣ��ѭ����������Ȳ��ع���Щ���½ڿ��һ�ϸ˵��
	while(GetMessage(&Msg,NULL,0,0))
    {
        TranslateMessage(&Msg);//������Ϣ
        DispatchMessage(&Msg);//������Ϣ
    }
    return Msg.message;
}

