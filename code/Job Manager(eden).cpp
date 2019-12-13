/*
 * declaration for class Job..
 */
#ifndef JOB_H

#include<string>
using namespace std;

class Job {
    public:
        explicit Job(int priority = 0);
        void setId(int id);
        int getId() const;
        void setPriority(int priority);
        int getPriority() const;
        void setNext(Job *job);
        Job *getNext() const;
        string toString();
    private:
        static int number;
        int id;
        int priority;
        Job *nextJob;
};

#endif


#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <iostream>

// disallow copy constructor and assignment operator
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class JobManager {
    public:
        // get the unique instance
        static JobManager* getInstance();
        static bool deleteInstance();

        void addJob(int priority = 0);
        void finishOneJob();
        void sortJob();
        void printJob();
        int getNumOfJob();
        void clear();

    private:
        Job * jobFrontPointer;
        ~JobManager();
        JobManager();
        static JobManager* instance;
        DISALLOW_COPY_AND_ASSIGN(JobManager);
};

#endif



#include <sstream>

using namespace std;

int Job::number = 0;

Job::Job(int priority){
	id = number;
	number++;
	this->priority = priority;
	nextJob = NULL;
}

void Job::setId(int id){
	this->id = id;
}

int Job::getId() const{
	return id;
}

void Job::setPriority(int priority){
	this->priority = priority;
}

int Job::getPriority() const{
	return priority;
}

void Job::setNext(Job *job){
	this->nextJob = job;
}

Job *Job::getNext() const{
	return nextJob;
}

string Job::toString(){
	stringstream ss;
	string str, str1, str2;
	ss << id;
	ss >> str1;
	ss.clear();
	ss << priority;
	ss >> str2;
	str = "[" + str1 + ":" + str2 + "]";
return str;
}

        

#include <iostream>

using namespace std;
  
JobManager* JobManager::instance = NULL;
// get the unique instance
JobManager* JobManager::getInstance(){
	if(instance == NULL)
	{
		instance = new JobManager();
	}
	return instance;
}

bool JobManager::deleteInstance(){
	if(instance == NULL)
	{
		return false;
	}
	delete instance;
	instance = NULL;
	return true;
}


void JobManager::addJob(int priority){
	Job *temp = new Job(priority);
	if(jobFrontPointer == NULL)
	{
		jobFrontPointer = temp;
		return;
	}
	Job* temp2 = jobFrontPointer;
	for(int i = 0; i < getNumOfJob() - 1; i++)
	{
		temp2 = temp2->getNext();
	}
	temp2->setNext(temp);
}

void JobManager::finishOneJob(){
	Job* temp = jobFrontPointer;
	if(temp == NULL)
	{
		return;
	}
	jobFrontPointer = jobFrontPointer->getNext();
	delete temp;
}

void JobManager::sortJob(){
	Job* temp = jobFrontPointer;
	int len = getNumOfJob();
	if(len == 0 || len == 1)
	{
		return;
	}
	int arr[len] = {0};
	int arr2[len] = {0};
	
	for(int i = 0; i < len; i++)
	{
		arr[i] = temp->getPriority();
		arr2[i] = temp->getId();
		temp = temp->getNext();
	}
	
	int num = 0;
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = i + 1; j < len; j++)
		{
			if(arr[i] < arr[j])
			{
				num = arr[i];
				arr[i] = arr[j];
				arr[j] = num; 
				num = arr2[i];
				arr2[i] = arr2[j];
				arr2[j] = num;
			}
			else if(arr[i] == arr[j])
			{
				if(arr2[i] > arr2[j])
				{ 
					num = arr2[i];
					arr2[i] = arr2[j];
					arr2[j] = num;
				}
			}
		}
	}
	
	temp = jobFrontPointer;
	for(int i = 0; i < len; i++)
	{
		temp->setPriority(arr[i]);
		temp->setId(arr2[i]);
		temp = temp->getNext();
	}
}

void JobManager::printJob(){
	int len = getNumOfJob();
	if(len == 0)
	{
		cout << "empty!" << endl;
		return;
	}
	Job* temp = jobFrontPointer;
	for(int i = 0; i < len - 1; i++)
	{
		cout << temp->toString() << "->";
		temp = temp->getNext();
	}
	cout << temp->toString() << endl;
}

int JobManager::getNumOfJob(){
	if(jobFrontPointer == NULL)
	{
		return 0;
	}
	Job* temp = jobFrontPointer;
	int i = 0;
	while(temp != NULL)
	{
		i++;
		temp = temp->getNext();
	}
return i;
}

void JobManager::clear(){
	if(jobFrontPointer == NULL)
	{
		return;
	}
	int len = getNumOfJob();
	Job* temp;
	for(int i = 0; i < len; i++)
	{
		temp = jobFrontPointer;
		jobFrontPointer = jobFrontPointer->getNext();
		delete temp;
	}
}

        
JobManager::~JobManager(){
	clear();
}

JobManager::JobManager(){
	jobFrontPointer = NULL;
}



using namespace std;

int main() {
    JobManager *manager1 = JobManager::getInstance();
    JobManager *manager2 = JobManager::getInstance();
    int pris[5] = {234, 23, 23432, 1, 5};
    for (int i = 0; i < 5; i++) {
        manager1->addJob(pris[i]);
    }
    manager2->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager1->finishOneJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager2->finishOneJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager1->addJob();
    manager1->addJob(6666);
    manager1->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager2->clear();
    manager1->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;

    int jobNum, jobPriority, deleteNum;
    cin >> jobNum;
    for (int i = 0; i < jobNum; i++) {
        cin >> jobPriority;
        manager2->addJob(jobPriority);
    }
    manager1->sortJob();
    manager2->printJob();
    cin >> deleteNum;
    while (deleteNum--) {
        manager1->finishOneJob();
    }
    manager1->printJob();
    cout << "The number of job is: " << manager2->getNumOfJob() << endl;

    if (JobManager::deleteInstance()) cout << "Delete successfully!\n";
    else cout << "Delete failure!\n";

    if (JobManager::deleteInstance()) cout << "Delete successfully!\n";
    else cout << "Delete failure!\n";
}


