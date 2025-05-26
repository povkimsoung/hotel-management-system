#include<iostream> 
#include <tabulate/table.hpp>
#include <xlnt/xlnt.hpp>
using namespace std;
using namespace tabulate;

// Encapsulation concept ! 
class Student {
    private: 
        string name; 
        int age; 
    public: 
        Student(string name, int age ){
            this-> name = name; 
            this -> age = age; 
        }
        string getName(){
            return name; 
        }
        int getAge(){
            return age; 
        }

        void setName(string name ){
            this-> name = name; 
        }
        void setAge(int age ){
            this-> age = age; 
        }
}; 


void printMenu(vector<string> items ){
    Table table; 
    table.add_row({"NO", "Menu "}); 
    for(int i = 0 ; i<items.size(); i++){
        table.add_row({to_string(i+1), items[i]});
    }
    table[0].format().font_style({FontStyle::bold});
    cout<<table<<endl; 
}

void printStudentTable(vector<Student> students){
    Table table; 
    table.add_row({"Name", "Age"}); 
    for(Student student : students){
        table.add_row({student.getName(),to_string(student.getAge())});
    }
    cout<<table<<endl; 
    
}

// Related to excel 
void writeVectorToExcel(string filename,
     vector<Student> students){
    xlnt::workbook wb; 
    auto ws = wb.active_sheet(); 
    ws.title("Sheet1"); 

    // table header 
    ws.cell("A1").value("Name"); 
    ws.cell("B1" ).value("Age");

    // insert all the data into row 
    int row = 2; 
    for(auto student: students){
        ws.cell("A"+to_string(row)).value(student.getName()); 
        ws.cell("B"+to_string(row)).value(student.getAge()); 
        row++; 
    }
    wb.save(filename); 
    cout<<"Successfuly saved vector to the excel file"<<endl; 

}

vector<Student> readStudentsFromExcel(const string& filename){
    vector<Student> students; 
    xlnt::workbook wb; 

     try{
         wb.load(filename); 
     }catch(...){
         cout<<"Excel file cannot be open for reading!! ❌"<<endl; 
         return students; 
     }
   
    // open sheet , loop through row and convert to vector 
    xlnt::worksheet ws = wb.active_sheet(); // Sheet1 
    for( auto row : ws.rows(false)){
        // skip table header 
        if( row[0].to_string()== "Name") continue; 

        string name; 
        int age; 
        name= row[0].to_string(); 
        age = stoi(row[1].to_string()); 

        Student student(name, age); 
        students.push_back(student); 
    }
    return students; 
}


int main(){
    system("clear"); 
    string filename = "studentdata.xlsx"; 
    vector<string> programMenu = {
        "Insert new student ", 
        "Edit Student info ", 
        "Delete Student ", 
        "Show All Student ", 
        "Exit"
    };
    int option; 
    vector<Student> studentLists = 
    readStudentsFromExcel(filename); 

    do{
        printMenu(programMenu); 
        cout<<"Choose you option : "; 
        cin>>option; 
        switch(option){
            case 1: 
            {
                string name; 
                int age; 
                cout<<"Enter Student Name: "; 
                cin.ignore();
                getline(cin,name); 
                cout<<"Enter Student Age : "; 
                cin>>age; 
                Student newStudent(name, age); 

                studentLists.push_back(newStudent); 
                writeVectorToExcel(filename,studentLists); 

            }
            break; 
            case 3: 
            {
                int row; // 1 , 2 , 3 
                cout<<"Enter row to delete : "; 
                cin>>row; 
                studentLists.erase(studentLists.begin() + row -1); 
                writeVectorToExcel(filename, studentLists); 
            }
            break; 
            case 4: 
                printStudentTable(studentLists); 
            break; 
        }
    }while(option!=5); 
    return 0 ; 
}