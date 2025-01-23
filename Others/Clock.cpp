clock_t start,finish;
double totaltime;
start=clock();
//...
finish=clock();
totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
cout<<"\n此程序的运行时间为"<<totaltime<<"秒！"<<endl;