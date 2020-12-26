#include <cstddef>
#include <cstdio>
#include<iostream>
#include <ostream>
#include<string.h>
#include <string>
#include <regex>
#include<tgmath.h>
#include "clase_sqlite.h"
using namespace std;

Database database;

int main()
{
    cout << "Test Class Content\n";
    Content a1;
    Content a2(2);
    Content a3("text");
    Content a4(4);
    a1 = a2;
    //cin >> a1;
    cout << a1;
    int b = a2[1];
    cout << b << endl;
    cout << !a3 << endl;
    if (a1 == a2)
    {
        cout << "a1 == a2" << endl;
    }
    if (a4 > a2)
    {
        cout << "a4 > a2" << endl;
    }
    cout << (int)a2 << endl;
    a2++;
    ++a2;
    a2 = a2 + 1;
    cout << "\n\n";
    cout << "Test Class Row\n";
    Row b1;
    Row b2(2);
    Content a5[3];
    a5[0] = a1; a5[1] = a2; a5[2] = a3;
    Row b3(a5, 4);
    b2 = b3;
    cin >> b1;
    b2 = b1;
    cout << b1;
    cout << "\n";
    cout << "Test Class Column\n";
    Column c1;
    Column c2("Mere", 10);
    Column c3("Pere", 2, 5);
    c1 = c3;
    cin >> c1;
    cout << c3;
    int a = c3[1];
    cout << a << endl;
    cout << !c3 << endl;
    if (c3 == c1)
    {
        cout << "c3 == c1" << endl;
    }
    if (c2 > c3)
    {
        cout << "c2 > c3" << endl;
    }
    cout << (int)c3 << endl;
    cout << c3.getColumnSize() << endl;
    c3++;
    cout << c3.getColumnSize() << endl;
    ++c3;
    cout << c3.getColumnSize() << endl;
    c3 = c3 + 1;
    cout << c3.getColumnSize() << endl;
    cout << endl;
    cout << "---The actual program---" << endl;
    string comanda;
    regex create_table ("^(CREATE TABLE ){1}([A-z]+)( IF NOT EXISTS)*(( \\()((\\(){1}([A-z]+(, ){1}(TEXT)*(INTEGER)*(FLOAT)*(, ){1}[0-9]+(, ){1}([A-z]*[0-9]*(.)*[0-9]*)*)(\\)(, )*){1})+(\\))){1}$");
    regex drop_table("^(DROP TABLE ){1}([A-z])+(\n)*$");
    regex display_table("^(DISPLAY TABLE ){1}([A-z])+$");
    regex insert_into("^(INSERT INTO){1}( )+([A-z])+( )+(VALUES){1}( )*(\\(){1}([A-z]*[0-9]*(.)*[0-9]*){1}((,)( )*[A-z]*[0-9]*(.)*[0-9]*)*(\\))$");
    regex delete_from("^(DELETE FROM){1}( )*([A-z,0-9]+[^WHERE]){1}( )*(WHERE){1}( )*([A-z,0-9]+){1}( )*(=){1}( )*([A-z,0-9]+){1}$");
    regex update("^(UPDATE ){1}([A-z0-9]+[^ SET]){1}( SET ){1}([A-z,0-9]+){1}( )*(=){1}( )*([A-z,0-9]+[^ WHERE]){1}( WHERE ){1}([A-z,0-9]+)( )*(=){1}( )*([A-z,0-9]+){1}$");
    cout << "To exit this cheap SQLite copy type \"exit\"\n";
    cout << ">> ";
    getline(cin,comanda,'\n');
    while(comanda!="exit")
    {
    if (regex_match (comanda,create_table))
    {
        if(comanda.find(" IF NOT EXISTS") == -1)
        {
            size_t pos1 = comanda.find(" (");
            size_t pos2;
            string table_name = comanda.substr(13,pos1-(comanda.find("LE ")+3));
            //cout << table_name << endl;
            pos1 += 3;
            database.createTable(table_name);
            while(pos1 < comanda.length())
            {
            pos2 = comanda.find(", ",pos1);
            string column_name = comanda.substr(pos1,pos2-pos1);
            pos1 = pos2 +2 ;
            pos2 = comanda.find(", ",pos1);
            string column_type = comanda.substr(pos1,pos2-pos1);
            pos1 = pos2 +2 ;
            pos2 = comanda.find(", ",pos1);
            string column_size = comanda.substr(pos1,pos2-pos1);
            pos1 = pos2 +2 ;
            pos2 = comanda.find(")",pos1);
            string default_value = comanda.substr(pos1,pos2-pos1);
            pos1 = pos2 + 4;
            database.addColumnToTable(table_name, column_name, column_type, column_size, default_value);
            }
            cout << "Table " << table_name << " created\n";
        }
        else
        {
            size_t pos1 = comanda.find(" IF");
            size_t pos2;
            string table_name = comanda.substr(13,pos1-(comanda.find("LE ")+3));
            if(database.findIndexOfTable(table_name)!=-1)
            {
                cout << "A table with the name " << table_name << " already exists";
            }
            else
            {
                pos1 = comanda.find(" (");
                pos1 += 3;
                database.createTable(table_name);
                while(pos1 < comanda.length())
                {
                    pos2 = comanda.find(", ",pos1);
                    string column_name = comanda.substr(pos1,pos2-pos1);
                    pos1 = pos2 +2 ;
                    pos2 = comanda.find(", ",pos1);
                    string column_type = comanda.substr(pos1,pos2-pos1);
                    pos1 = pos2 +2 ;
                    pos2 = comanda.find(", ",pos1);
                    string column_size = comanda.substr(pos1,pos2-pos1);
                    pos1 = pos2 +2 ;
                    pos2 = comanda.find(")",pos1);
                    string default_value = comanda.substr(pos1,pos2-pos1);
                    pos1 = pos2 + 4;
                    database.addColumnToTable(table_name, column_name, column_type, column_size, default_value);
                }
            }
            cout << "Table " << table_name << " created\n";
        }
    }

    if (regex_match (comanda,drop_table))
    {
        string table_name = comanda.substr(11,comanda.length()-11);
        database.dropTable(table_name);
    }

    if (regex_match (comanda,display_table))
    {
        cout << "aici facem display table";
    }

    if (regex_match (comanda,insert_into))
    {
        size_t pos1 = comanda.find(" VALUES");
        size_t pos2;
        string table_name = comanda.substr(12,pos1-12);
        int table_index = database.findIndexOfTable(table_name);
        if(table_index==-1)
        {
            cout << "The table " << table_name << " doesn't exist\n";
        }
        else
        {
            comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
            pos1 = comanda.find("(")+1;
            int nr_of_values = 1;
            for(int i = pos1;i<comanda.length();i++)
            {
                if(comanda[i] == ',')
                    nr_of_values++;
            }
            if(database.getNrOfColumnsOfTable(table_name) != nr_of_values)
            {
                cout << "The number of values typed for table " << table_name << " doesn't match the number of columns in that table\n";
            }
            else
            {
                database.getTable(table_name).addRow();
                string value;
                int column_nr = 0;
                while(pos1 < comanda.length())
                {
                    pos2 = comanda.find(',',pos1);
                    if(pos2 == string::npos)
                    {
                        pos2 = comanda.find(')',pos1);
                    }
                    value = comanda.substr(pos1,pos2-pos1);
                    pos1 = pos2 + 1;
                    if(database.getTable(table_name).getColumnTypeByIndex(column_nr)!=3)
                    {
                        int i=0;

                        if(database.getTable(table_name).getColumnTypeByIndex(column_nr)==1)
                        {
                            regex integer("^([0-9]+)$");
                            if (!(regex_match(value,integer)))
                            {
                                cout << "ERROR: Column type for column " << database.getTable(table_name).getColumnNameByIndex(column_nr) << " in table " << table_name << "is INTEGER\n";
                            }
                            else
                            {
                                Content new_value(stoi(value));
                                database.getTable(table_name).addValueToRow(new_value, 1);

                            }
                        }

                        if(database.getTable(table_name).getColumnTypeByIndex(column_nr)==2)
                        {
                            regex floating("^((.)*[0-9]+(.)*[0-9]*)$");
                            if (!(regex_match(value,floating)))
                            {
                                cout << "ERROR: Column type for column " << database.getTable(table_name).getColumnNameByIndex(column_nr) << " in table " << table_name << " is FLOAT\n";
                            }
                            else
                            {
                                Content new_value(stof(value));
                                database.getTable(table_name).addValueToRow(new_value, 2);
                            }
                        }
                    }
                    else
                    {
                        Content new_value(value);
                        database.getTable(table_name).addValueToRow(new_value, 3);

                    }
                    column_nr++;
                }
            }
            cout << "Row added to table " << table_name << "\n";
        }
    }
    if(regex_match(comanda,delete_from))
    {
        comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
        size_t pos1 = comanda.find("WHERE");
        size_t pos2;
        string table_name = comanda.substr(10,pos1-10);
        if(database.findIndexOfTable(table_name)==-1)
        {
            cout << "There is no table named " << table_name << " in the database\n";
        }
        else
        {
            pos1 += 5;
            pos2 = comanda.find('=',pos1);
            string column = comanda.substr(pos1,pos2-pos1);
            if(database.getTable(table_name).columnIndexByName(column)==-1)
            {
                cout << "There is no column named " << column << " in table " << table_name << endl;
            }
            else
            {
                string column_value = comanda.substr(pos2+1,comanda.length()-pos1);
                database.getTable(table_name).deleteFrom(column, column_value);
            }
        }
    }
    cout << ">> ";
    getline(cin,comanda,'\n');
    }
    database.getTables();
}

//CREATE TABLE test ((a, TEXT, 3, a), (b, INTEGER, 3, 0), (c, FLOAT, 3, 9.2))
//INSERT INTO test VALUES (xz, 12, 1.3)
