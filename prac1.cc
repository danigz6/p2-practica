#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

bool checkDay(Project &toDoList, string dateTask){
	int first=0;
	int second=0;
	int day=0;
	bool good = false;
	
	first = dateTask[0] - '0';
	second = dateTask[1] - '0';
	day = (first*10)+second;
	
	if (day > 0 && day <= 31){
		good = true;
	}
	else{
		error(ERR_DATE);
	}
	cout << day <<endl;

	return good;
}

bool checkMonth(Project &toDoList, string dateTask){
	int first=0;
	int second=0;
	int month=0;
	int day = 0;
	bool good = false;
	
	first = dateTask[3] - '0';
	second = dateTask[4] - '0';
	month = (first*10)+second;
	
	if (month >= 1 && month <= 12){
		good = true;
	}
	else{
		error(ERR_DATE);
	}
	
	if (month == 2 && day > 28){
		error(ERR_DATE);
	}
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30){
		error(ERR_DATE);
	}
	
	cout << month <<endl;

	return good;
}

bool checkYear(Project &toDoList, string dateTask){
	int first=0;
	int second=0;
	int third=0;
	int fourth=0;
	int year=0;
	bool good = false;
	
	first = dateTask[6] - '0';
	second = dateTask[7] - '0';
	third = dateTask[8] - '0';
	fourth = dateTask[9] - '0';
	year = (first*1000)+(second*100)+(third*10)+fourth;
	
	if (year >= 2000 && year <= 2100){
		good = true;
	}
	else{
		error(ERR_DATE);
	}
	
	cout << year <<endl;

	return good;
}

int searchList(Project &toDoList, string nameList){
	int position = -1;

    for (unsigned int i = 0; i < toDoList.lists.size(); i++) { 
        if (toDoList.lists[i].name == nameList) {
           position = i;
        }
    } 

    return position;
}

int searchTask(Project &toDoList, string nameTask){
	int position=-1;

    for (unsigned int i = 0; i < toDoList.lists.size(); i++) { 
        for (unsigned int j = 0; j < toDoList.lists[i].tasks.size(); j++ ) {
            if (toDoList.lists[i].tasks[j].name == nameTask) {
                position=j;
            }
        } 
    }

    return position;
}

bool existList(Project &toDoList, string nameList){
	bool exist=false;

    for (unsigned int i = 0; i < toDoList.lists.size() && exist==false; i++) { 
        if (toDoList.lists[i].name == nameList) {
           exist =true;
        }
    } 

    return exist;
}

void editProject(Project &toDoList){
	string nameProject;
	string description;
	
	do{
		cout << "Enter project name: "; 
	    getline(cin,nameProject);
		
		if (nameProject==""){
			error(ERR_EMPTY);
		}
		
	}while(nameProject=="");
	
	toDoList.name=nameProject;
	
	cout << "Enter project description: ";
	getline(cin,nameProject);
}

void addList(Project &toDoList){
	List newList;
    string nameList;
    bool exist=false;

	do{
		cout << "Enter list name: "; 
		getline(cin,nameList);
		
		if (nameList==""){
			error(ERR_EMPTY);
		}
		
	}while(nameList=="");
	
	exist=existList(toDoList,nameList); 
	
	if (exist==false){
      newList.name=nameList;
      toDoList.lists.push_back(newList);
    }
    else{
      error(ERR_LIST_NAME);
    }
}

void deleteList(Project &toDoList){
	string nameList;
	int position=0;
	
	do{
		cout << "Enter list name: "; 
		getline(cin,nameList);
		
		if (nameList==""){
			error(ERR_EMPTY);
		}
		
	}while(nameList=="");
	
	position=searchList(toDoList,nameList);
	
	if (position == -1){
		error(ERR_LIST_NAME);
	}
	else{
		toDoList.lists.erase(toDoList.lists.begin() + position);
	}
}

void addTask(Project &toDoList){
	string nameList;
	string nameTask;
	string dateTask;
	int positionList = 0;
	int positionTask = 0;
	
	do{
		cout << "Enter list name: "; 
		getline(cin,nameList);
		
		if (nameList==""){
			error(ERR_EMPTY);
		}
		
	}while(nameList=="");
	
	positionList=searchList(toDoList,nameList);
	positionTask=searchTask(toDoList,nameList);
	
	if (positionList==-1){
		error(ERR_LIST_NAME);
	}
	else{
		cout << "Enter task name: ";
		getline(cin,nameTask);
	}
	
	cout << "Enter deadline: ";
	cin >> dateTask;
	
	toDoList.lists[positionList].tasks[positionTask].isDone=false;
}

void deleteTask(Project &toDoList){
	string nameList;
	string nameTask;
	int positionList=0;
	int positionTask=0;
	
	do{
		cout << "Enter list name: "; 
		getline(cin,nameList);
		
		if (nameList==""){
			error(ERR_EMPTY);
		}
		
	}while(nameList=="");
	
	positionList=searchList(toDoList,nameList);
	
	if (positionList==-1){
		error(ERR_LIST_NAME);
	}
	else{
		cout << "Enter task name: ";
		getline(cin,nameTask);
	}
	
	positionTask=searchTask(toDoList,nameTask);
	
	if (positionTask==-1){
		error(ERR_TASK_NAME);
	}
	else{
		toDoList.lists[positionList].tasks.erase(toDoList.lists[positionList].tasks.begin() + positionTask);
	}	
}

void toggleTask(Project &toDoList){
	string nameList;
	string nameTask;
	int positionList=0;
	int positionTask=0;
	
	do{
		cout << "Enter list name: "; 
		getline(cin,nameList);
		
		if (nameList==""){
			error(ERR_EMPTY);
		}
		
	}while(nameList=="");
	
	positionList=searchList(toDoList,nameList);
	
	if (positionList==-1){
		error(ERR_LIST_NAME);
	}
	else{
		cout << "Enter task name: ";
		getline(cin,nameTask);
	}
	
	positionTask=searchTask(toDoList,nameTask);
	
	if (positionTask==-1){
		error(ERR_TASK_NAME);
	}
	else{
		toDoList.lists[positionList].tasks[positionTask].isDone=!toDoList.lists[positionList].tasks[positionTask].isDone;
	}
}

void report(const Project &toDoList){
	
	cout << "Name: " << "cama"<<endl;
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
