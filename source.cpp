#include<iostream>
#include <string>
#include <regex>
#include<tgmath.h>
#include<iomanip>
#include "clase_sqlite.h"
using namespace std;

Database database;

int main(int argc, char** argv)
{
    /* cout << "Test Class Content\n";
     Content a1;
     Content a2(2);
     Content a3("text");
     Content a4(4);
     cin >> a1;
     cout << a1;
     a2 = a1;
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
     cout << b2;
     cout << "\n";
     cout << "Test Class Column\n";
     Column c1;
     Column c2("Mere", 10);
     Column c3("Pere", 2, 5);
     cin >> c1;
     cout << c3;
     c1 = c3;
     int a = c3[1];
     cout << a << endl;
     cout << !c3 << endl;
     if (c3 == c1)
     {
         cout << "c3 == c1" << endl;
     }
     if (c1 > c2)
     {
         cout << "c1 > c2" << endl;
     }
     cout << (int)c3 << endl;
     cout << c3.getColumnSize() << endl;
     c3++;
     cout << c3.getColumnSize() << endl;
     ++c3;
     cout << c3.getColumnSize() << endl;
     c3 = c3 + 1;
     cout << c3.getColumnSize() << endl;*/
     /* cout << endl << "Test table class\n";
      Table t1;
      Table t2("test", 2,2);
      Table t3("test", 2, 2);
      cin >> t1;
      cout << t1;
      Row b6(t1[0]);
      cout << b6 << endl;
      t2 = t3;
      cout << !t3 << endl;
      if (t3 == t2)
      {
          cout << "t3 == t2" << endl;
      }
      if (t3 > t1)
      {
          cout << "t3 > t1" << endl;
      }
      cout << (int)t1 << endl;
     t3++;
     ++t3;*/
     //cout << "Test Class Database\n";
     //Database d1;
     //Database d2(3);
     //Table* test_tables;
     //test_tables = new Table[3];
     //test_tables[0] = t1;
     //test_tables[1] = t2;
     //test_tables[2] = t3;
     //Database d3(3, test_tables);
     //cout << d3;
     //cout << endl;
     //cin >> d2;
     //cout << endl;
     //cout << d2;
     //cout << !d3;
     //cout << endl;
     //Database d4 = d3;
     //if (d3 == d4)
     //{
     //    cout << "d3 == d4\n";
     //}
     //if (d3 > d1)
     //{
     //    cout << "d3 > d1\n";
     //}
     //cout << (int)d3 << endl;
     //d3++;
     ////d4 = d3 + t3;
     //++d3;
     //Table t4(d3[1]);
     // cout << endl;
    if (argc <= 6)
    {
        Input input(argc, argv);
        cout << "Running commands from input files...\n";
        input.runCommands(database);
    }
    else
    {
        cout << "Only 5 command line arguments allowed! Aborting reading commands from argument files...\n";
    }
    cout << "---The actual program---" << endl;
    string comanda;
    regex create_table("^(CREATE( )*TABLE( )*){1}([A-z]+[0-9]*){1}(( )*IF NOT EXISTS)*( )*((\\()((\\(){1}([A-z]+(,){1}( )*(TEXT)*(INTEGER)*(FLOAT)*(,){1}( )*[0-9]+(,){1}( )*([A-z]*[0-9]*(\\.)*[0-9]*)*)(\\)(,)*( )*){1})+(\\))){1}$");
    regex drop_table("^(DROP TABLE){1}( )*([A-z]+[0-9]){1}$");
    regex display_table("^(DISPLAY TABLE ){1}([A-z])+$");
    regex insert_into("^(INSERT INTO){1}( )*([A-z0-9])+( )*(VALUES){1}( )*(\\(){1}([A-z]*[0-9]*(\\.)*[0-9]*){1}((,)*( )*[A-z]*[0-9]*(.)*[0-9]*)*(\\))$");
    regex delete_from("^(DELETE FROM){1}( )*([A-z0-9]+[^WHERE]){1}( )*(WHERE){1}( )*([A-z0-9]+){1}( )*(=){1}( )*([A-z0-9]+(\.)*[0-9]*){1}$");
    regex update("^(UPDATE ){1}([A-z0-9]+){1}( SET ){1}([A-z0-9]+){1}( )*(=){1}( )*([A-z0-9]+){1}( WHERE ){1}([A-z0-9]+)( )*(=){1}( )*([A-z0-9]+){1}$");
    regex select("^(SELECT){1}( ){1}([A-z0-9]+){1}((,){1}( ){1}[A-z0-9]+)*( ){1}(FROM){1}( ){1}([A-z0-9]+){1}(( ){1}(WHERE){1}( ){1}([A-z0-9])+( ){1}(=){1}( ){1}([A-z0-9]+(\.)*[0-9]*){1})*$");
    cout << "To exit this cheap database manager type \"exit\"\n";
    cout << "Accepted commands (examples):\nCREATE TABLE test ((a, TEXT, 3, a), (b, INTEGER, 3, 0), (c, FLOAT, 3, 9.2), (...))\nINSERT INTO test VALUES (xz, 12, 1.3, ...)\nDELETE FROM test WHERE a = xz\nDROP TABLE test\n";
    cout << ">> ";
    getline(cin, comanda, '\n');
    while (comanda != "exit")
    {
        int valid = 0;
        if (regex_match(comanda, select))
        {
            valid = 1;
            int nr_of_columns=1;
            size_t pos1 = 7;
            size_t pos2;
            for (int i = pos1; i < comanda.find(" FROM"); i++)
            {
                if (comanda[i] == ',')
                    nr_of_columns++;
            }
            string* columns;
            columns = new string[nr_of_columns];
            for (int i = 0; i < nr_of_columns-1; i++)
            {
                pos2 = comanda.find(",", pos1);
                columns[i] = comanda.substr(pos1, pos2 - pos1);
                cout << columns[i] << endl;
                pos1 = pos2 + 2;
            }
            pos2 = comanda.find(" FROM");
            columns[nr_of_columns - 1] = comanda.substr(pos1, pos2-pos1);
            cout << columns[nr_of_columns - 1] << endl;
            pos1 = pos2 + 6;
            pos2 = comanda.find(" WHERE");
            string table_name;
            string criterium_column;
            string criterium_value;
            if (pos2 != -1)
            {
                table_name = comanda.substr(pos1, pos2 - pos1);
                //cout << table_name << endl;
                pos1 = pos2 + 7;
                pos2 = comanda.find(" =", pos1);
                criterium_column = comanda.substr(pos1, pos2-pos1);
                //cout << criterium_column << endl;
                pos1 = pos2 + 3;
                criterium_value = comanda.substr(pos1, comanda.length() - pos1);
                //cout << criterium_value << endl;
                if (database.getTable(table_name).columnIndexByName(criterium_column) != -1)
                {
                    if (nr_of_columns == 1 && columns[0] == "ALL")
                    {
                        database.getTable(table_name).select(1, columns,nr_of_columns,1, criterium_column, criterium_value);
                    }
                    else
                    {
                        database.getTable(table_name).select(0, columns, nr_of_columns, 1, criterium_column, criterium_value);
                    }
                }
                else
                {
                    cout << "Column " << criterium_column << " doesn't exist, update statement aborted.\n";
                }
            }
            else
            {
                table_name = comanda.substr(pos1, comanda.length() - pos1);
                //cout << table_name << endl;
                if (nr_of_columns == 1 && columns[0] == "ALL")
                {
                    database.getTable(table_name).select(1, columns, nr_of_columns, 0, criterium_column, criterium_value);
                }
                else
                {
                    database.getTable(table_name).select(0, columns, nr_of_columns, 0, criterium_column, criterium_value);
                }
            }
        }
        if (regex_match(comanda, create_table))
        {
            valid = 1;
            regex ifnotexists("^(.)+(IF){1}( )*(NOT){1}( )*(EXISTS){1}(.)+$");
            if (!(regex_match(comanda, ifnotexists)))
            {
                comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
                size_t pos1 = comanda.find("(");
                size_t pos2;
                string table_name = comanda.substr(11, pos1 - 11);
                if (database.findIndexOfTable(table_name) != -1)
                {
                    cout << "A table with the name " << table_name << " already exists";
                }
                else
                {
                    pos1 += 2;
                    database.createTable(table_name);
                    while (pos1 < comanda.length())
                    {
                        pos2 = comanda.find(",", pos1);
                        string column_name = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 1;
                        pos2 = comanda.find(",", pos1);
                        string column_type = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 1;
                        pos2 = comanda.find(",", pos1);
                        string column_size = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 1;
                        pos2 = comanda.find(")", pos1);
                        string default_value = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 3;
                        database.addColumnToTable(table_name, column_name, column_type, column_size, default_value);
                    }
                    cout << "Table " << table_name << " created\n";
                }
            }
            else
            {
                comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
                size_t pos1 = comanda.find("(");
                size_t pos2;
                string table_name = comanda.substr(11, pos1 - 22);
                if (database.findIndexOfTable(table_name) != -1)
                {
                    cout << "A table with the name " << table_name << " already exists";
                }
                else
                {
                    pos1 = comanda.find("(");
                    pos1 += 2;
                    database.createTable(table_name);
                    while (pos1 < comanda.length())
                    {
                        pos2 = comanda.find(",", pos1);
                        string column_name = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 1;
                        pos2 = comanda.find(",", pos1);
                        string column_type = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 1;
                        pos2 = comanda.find(",", pos1);
                        string column_size = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 1;
                        pos2 = comanda.find(")", pos1);
                        string default_value = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 3;
                        database.addColumnToTable(table_name, column_name, column_type, column_size, default_value);
                    }
                    cout << "Table " << table_name << " created\n";
                }
            }
        }

        if (regex_match(comanda, drop_table))
        {
            valid = 1;
            comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
            string table_name = comanda.substr(10, comanda.length() - 10);
            database.dropTable(table_name);
        }

        if (regex_match(comanda, display_table))
        {
            valid = 1;
            comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
            string table_name = comanda.substr(12, comanda.length() - 12);
            database.getTable(table_name).display();
        }

        if (regex_match(comanda, insert_into))
        {
            valid = 1;
            size_t pos1 = comanda.find(" VALUES");
            size_t pos2;
            string table_name = comanda.substr(12, pos1 - 12);
            int table_index = database.findIndexOfTable(table_name);
            if (table_index == -1)
            {
                cout << "The table " << table_name << " doesn't exist\n";
            }
            else
            {
                comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
                pos1 = comanda.find("(") + 1;
                int nr_of_values = 1;
                for (int i = pos1; i < comanda.length(); i++)
                {
                    if (comanda[i] == ',')
                        nr_of_values++;
                }
                if (database.getNrOfColumnsOfTable(table_name) > nr_of_values)
                {
                    cout << "The number of values typed for table " << table_name << " is bigger than the number of columns in that table\n";
                }
                else
                {
                    database.getTable(table_name).addRow();
                    string value;
                    int column_nr = 0;
                    while (pos1 < comanda.length())
                    {
                        pos2 = comanda.find(',', pos1);
                        if (pos2 == string::npos)
                        {
                            pos2 = comanda.find(')', pos1);
                        }
                        value = comanda.substr(pos1, pos2 - pos1);
                        pos1 = pos2 + 1;
                        if (database.getTable(table_name).getColumnTypeByIndex(column_nr) != 3)
                        {
                            int i = 0;

                            if (database.getTable(table_name).getColumnTypeByIndex(column_nr) == 1)
                            {
                                regex integer("^([0-9]+)$");
                                if (!(regex_match(value, integer)))
                                {
                                    cout << "ERROR: Column type for column " << database.getTable(table_name).getColumnNameByIndex(column_nr) << " in table " << table_name << "is INTEGER\n";
                                }
                                else
                                {
                                    Content new_value(stoi(value));
                                    database.getTable(table_name).addValueToRow(new_value, 1);

                                }
                            }

                            if (database.getTable(table_name).getColumnTypeByIndex(column_nr) == 2)
                            {
                                regex floating("^((.)*[0-9]+(.)*[0-9]*)$");
                                if (!(regex_match(value, floating)))
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
        if (regex_match(comanda, delete_from))
        {
            valid = 1;
            comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
            size_t pos1 = comanda.find("WHERE");
            size_t pos2;
            string table_name = comanda.substr(10, pos1 - 10);
            if (database.findIndexOfTable(table_name) == -1)
            {
                cout << "There is no table named " << table_name << " in the database\n";
            }
            else
            {
                pos1 += 5;
                pos2 = comanda.find('=', pos1);
                string column = comanda.substr(pos1, pos2 - pos1);
                if (database.getTable(table_name).columnIndexByName(column) == -1)
                {
                    cout << "There is no column named " << column << " in table " << table_name << endl;
                }
                else
                {
                    string column_value = comanda.substr(pos2 + 1, comanda.length() - pos1);
                    database.getTable(table_name).deleteFrom(column, column_value);
                }
            }
        }
        if (regex_match(comanda, update))
        {
            valid = 1;
            comanda.erase(remove(comanda.begin(), comanda.end(), ' '), comanda.end());
            size_t pos1 = comanda.find("SET");
            size_t pos2;
            string table_name = comanda.substr(6, pos1 - 6);
            if (database.findIndexOfTable(table_name) == -1)
            {
                cout << "There is no table named " << table_name << " in the database\n";
            }
            else
            {
                pos2 = pos1 + 3;
                pos1 = comanda.find("=", pos2);
                string column_to_update = comanda.substr(pos2, pos1 - pos2);
                pos2 = pos1 + 1;
                pos1 = comanda.find("WHERE", pos2);
                string updated_value = comanda.substr(pos2, pos1 - pos2);
                pos2 = pos1 + 5;
                pos1 = comanda.find("=", pos2);
                string criterium_column = comanda.substr(pos2, pos1 - pos2);
                pos1 += 1;
                string criterium_value = comanda.substr(pos1, comanda.length() - pos1);
                if (database.getTable(table_name).columnIndexByName(criterium_column) != -1)
                {
                    if (database.getTable(table_name).columnIndexByName(column_to_update) != -1)
                    {
                        database.getTable(table_name).update(column_to_update, updated_value, criterium_column, criterium_value);
                    }
                    else
                    {
                        cout << "Column " << column_to_update << " doesn't exist, update statement aborted.\n";
                    }
                }
                else
                {
                    cout << "Column " << criterium_column << " doesn't exist, update statement aborted.\n";
                }
            }
        }
        if (valid == 0)
        {
            cout << "Command not recognized, try again or type \"exit\"\n";
        }
        cout << ">> ";
        getline(cin, comanda, '\n');
    }
}

//CREATE TABLE test ((a, TEXT, 3, a), (b, INTEGER, 3, 0), (c, FLOAT, 3, 9.2))
//INSERT INTO test VALUES (xx, 11, 1.1)
//INSERT INTO test VALUES (yy, 22, 2.2)
//INSERT INTO test VALUES(zz, 33, 3.3)
//DISPLAY TABLE test
//UPDATE test SET a = yz WHERE b = 12
