#include<iostream>
#include <string>
#include <regex>
#include<tgmath.h>
using namespace std;

class Content
{
public:
    Content()
    {
        int_content = 0;
        float_content = 0;
        text_content = "";
        content_type = 0;
    }
    Content(int content)
    {
        int_content = content;
        content_type = 1;
        float_content = 0;
        text_content = "";
    }
    Content(float content)
    {
        float_content = content;
        content_type = 2;
        text_content = "";
        int_content = 0;
    }
    Content(string content)
    {
        text_content = content;
        content_type = 3;
        int_content = 0;
        float_content = 0;
    }

    Content(Content& c)
    {
        this->content_type = c.content_type;
        if (c.content_type == 1)
        {
            this->int_content = c.int_content;
            float_content = 0;
            text_content = "";
        }
        if (c.content_type == 2)
        {
            this->float_content = c.float_content;
            text_content = "";
            int_content = 0;
        }
        if (c.content_type == 3)
        {
            this->text_content = c.text_content;
            int_content = 0;
            float_content = 0;
        }
    }

    Content& operator=(Content& c)
    {
        this->content_type = c.content_type;
        if (c.content_type == 1)
        {
            this->int_content = c.int_content;
        }
        if (c.content_type == 2)
        {
            this->float_content = c.float_content;
        }
        if (c.content_type == 3)
        {
            this->text_content = c.text_content;
        }

        return *this;
    }

    void print()
    {
        if (content_type == 1)
        {
            cout << this->int_content << endl;
        }
        if (content_type == 2)
        {
            cout << this->float_content << endl;
        }
        if (content_type == 3)
        {
            cout << this->text_content << endl;
        }
    }

    int getIntContent()
    {
        return int_content;
    }

    float getFloatContent()
    {
        return float_content;
    }

    string getTextContent()
    {
        return text_content;
    }

    int getContentType()
    {
        return content_type;
    }

    void setIntContent(int x)
    {
        if(content_type == 1)
            int_content = x;
        else
        {
            cout << "content type for object is not integer\n";
        }
    }

    void setFloatContent(float x)
    {
        if (content_type == 2)
            float_content = x;
        else
        {
            cout << "content type for object is not float\n";
        }
    }

    void setTextContent(string x)
    {
        if (content_type == 3)
            text_content = x;
        else
        {
            cout << "content type for object is not text\n";
        }
    }

    void setContentType(int x)
    {
        if (x != 1 && x != 2 && x != 3)
        {
            cout << "not a valid content type";
        }
        else
        {
            content_type = x;
        }
    }

    bool operator!()
    {
        return content_type == 0;
    }

    Content operator++()
    {
        if (content_type == 1)
        {
            this->int_content++;
        }
        if (content_type == 2)
        {
            this->float_content++;
        }
        if (content_type == 3)
        {
            throw exception("This object has text type");
        }
        return *this;
    }

    Content operator++(int i)
    {
        Content content_copy = *this;
        if (content_type == 1)
        {
            this->int_content++;
        }
        if (content_type == 2)
        {
            this->float_content++;
        }
        if (content_type == 3)
        {
            throw exception("This object has text type");
        }
        return content_copy;
    }

    Content& operator+(int n)
    {
        Content content_copy = *this;
        if (content_type == 1)
        {
            content_copy.int_content += n;
        }
        if (content_type == 2)
        {
            content_copy.float_content += n;
        }
        if (content_type == 3)
        {
            throw exception("This object has text type");
        }
        return content_copy;
    }

    int operator[](int index)
    {
        if (index == 1 && content_type == 1)
        {
            return int_content;
        }
        if (index == 2 && content_type == 2)
        {
            return (int)float_content;
        }
        if (index != 1 && index != 2)
        {
            throw exception("Bad index");
        }
        if (content_type == 0)
        {
            throw exception("Object with uninitialized content");
        }
    }

    explicit operator int()
    {
        if (content_type == 1)
            return int_content;
        else
            throw exception("Column doesn't have integer type");
    }

    bool operator>(Content c)
    {
        if (content_type == 1 && content_type == c.content_type)
            return this->int_content > c.int_content;
        if (content_type == 2 && content_type == c.content_type)
            return this->float_content > c.float_content;
        if (content_type == 3 && content_type == c.content_type)
            return this->text_content > c.text_content;
        return false;
    }

    bool operator==(Content c)
    {
        return this->content_type == c.content_type;
    }

    friend ostream& operator<<(ostream&, Content&);
    friend istream& operator>>(istream&, Content&);

private:
    int int_content;
    float float_content;
    string text_content;
    // 0 - null/uninitialized, 1 - int, 2 - float, 3 - string
    int content_type;
};

ostream& operator<<(ostream& o, Content& c)
{
    if (c.content_type == 1)
    {
        o << c.int_content << " ";
    }
    if (c.content_type == 2)
    {
        o << c.float_content << " ";
    }
    if (c.content_type == 3)
    {
        o << c.text_content << " ";
    }
    return o;
}

istream& operator>>(istream& i, Content& c)
{
    cout << "Content type? (int - 1, float - 2, text - 3): ";
    i >> c.content_type;
    if (c.content_type == 1)
    {
        i >> c.int_content;
    }
    if (c.content_type == 2)
    {
        i >> c.float_content;
    }
    if (c.content_type == 3)
    {
        i >> c.text_content;
    }

    return i;
}

class Row
{
public:
    Row()
    {
        values = nullptr;
        nr_of_values = 0;
    }
    ~Row()
    {
        if (values != nullptr)
            delete[] values;
    }
    Row(int nr_of_values)
    {
        if (nr_of_values > 0)
        {
            this->nr_of_values = nr_of_values;
            this->values = new Content[this->nr_of_values];
        }
        else
        {
            this->nr_of_values = 0;
            this->values = nullptr;
        }

    }
    Row(Content* values, int nr_of_values)
    {
        if (nr_of_values > 0)
        {
            this->nr_of_values = nr_of_values;
            this->values = new Content[this->nr_of_values];
            for (int i = 0; i < nr_of_values; i++)
            {
                this->values[i] = values[i];
            }
        }
        else
        {
            this->nr_of_values = 0;
            this->values = nullptr;
        }
    }
    Row(Row& r)
    {
        if (r.values != nullptr && r.nr_of_values != 0)
        {
            this->nr_of_values = r.nr_of_values;
            if (this->values != nullptr)
            {
                delete[] this->values;
            }
            this->values = new Content[r.nr_of_values];
            for (int i = 0; i < r.nr_of_values; i++)
            {
                this->values[i] = r.values[i];
            }
        }
        else
        {
            this->nr_of_values = 0;
            this->values = nullptr;
        }
    }

    Row& operator=(const Row& r)
    {
        this->nr_of_values = r.nr_of_values;
        if (this->values != nullptr)
        {
            delete[] this->values;
        }
        if (r.values != nullptr && r.nr_of_values != 0)
        {
            
            this->values = new Content[r.nr_of_values];
            for (int i = 0; i < r.nr_of_values; i++)
            {
                this->values[i] = r.values[i];
            }
        }
        else
        {
            this->values = nullptr;
        }
        return *this;
    }

    bool operator!()
    {
        return nr_of_values == 0;
    }

    Row operator++()
    {
        if (values != nullptr && nr_of_values != 0)
        {
            Content* values_copy;
            values_copy = new Content[nr_of_values];
            for (int i = 0; i < nr_of_values; i++)
            {
                values_copy[i] = values[i];
            }
            nr_of_values++;
            delete[] values;
            values = new Content[nr_of_values];
            for (int i = 0; i < nr_of_values - 1; i++)
            {
                values[i] = values_copy[i];
            }
            delete[] values_copy;
        }
        else
        {
            nr_of_values = 1;
            values = new Content[1];
        }
        return *this;
    }

    Row operator++(int i)
    {
        Row content_copy = *this;
        if (values != nullptr && nr_of_values != 0)
        {
            Content* values_copy;
            values_copy = new Content[nr_of_values];
            for (int i = 0; i < nr_of_values; i++)
            {
                values_copy[i] = values[i];
            }
            nr_of_values++;
            delete[] values;
            values = new Content[nr_of_values];
            for (int i = 0; i < nr_of_values - 1; i++)
            {
                values[i] = values_copy[i];
            }
            delete[] values_copy;
        }
        else
        {
            nr_of_values = 1;
            values = new Content[1];
        }
        return content_copy;
    }

    Row& operator+(Content c)
    {
        Row content_copy = *this;
        if (content_copy.values != nullptr && content_copy.nr_of_values != 0)
        {
            Content* values_copy;
            values_copy = new Content[content_copy.nr_of_values];
            for (int i = 0; i < content_copy.nr_of_values; i++)
            {
                values_copy[i] = content_copy.values[i];
            }
            content_copy.nr_of_values += 1;
            delete[] content_copy.values;
            content_copy.values = new Content[content_copy.nr_of_values];
            for (int i = 0; i < content_copy.nr_of_values - 1; i++)
            {
                content_copy.values[i] = values_copy[i];
            }
            content_copy[nr_of_values - 1] = c;
            delete[] values_copy;
        }
        else
        {
            content_copy.nr_of_values = 1;
            content_copy.values = new Content[1];
            content_copy.values[0] = c;
        }
        return content_copy;
    }

    Content& operator[](int index)
    {
        return this->values[index];
    }

    explicit operator int()
    {
        return this->nr_of_values;
    }

    bool operator>(Row c)
    {
        return this->nr_of_values > c.nr_of_values;

    }

    bool operator==(Row c)
    {
        if (this->nr_of_values == c.nr_of_values)
        {
            for (int i = 0; i < this->nr_of_values; i++)
            {
                if (!(this->values[i] == c.values[i]))
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    void setNewRow(Row r)
    {
        if (r.values != nullptr && r.nr_of_values != 0)
        {
            this->nr_of_values = r.nr_of_values;
            if (this->values != nullptr)
            {
                delete[] this->values;
            }
            this->values = new Content[r.nr_of_values];
            for (int i = 0; i < r.nr_of_values; i++)
            {
                this->values[i] = r.values[i];
            }
        }
        else
        {
            this->nr_of_values = 0;
            this->values = nullptr;
        }
    }

    void addValue(Content new_value, int type)
    {
        if (values != nullptr && nr_of_values != 0)
        {
            Content* values_copy;
            values_copy = new Content[nr_of_values];
            for (int i = 0; i < nr_of_values; i++)
            {
                values_copy[i] = values[i];
            }
            nr_of_values++;
            delete[] values;
            values = new Content[nr_of_values];
            for (int i = 0; i < nr_of_values - 1; i++)
            {
                values[i] = values_copy[i];
            }
            values[nr_of_values - 1] = new_value;
            delete[] values_copy;
        }
        else
        {
            nr_of_values = 1;
            values = new Content[1];
            values[0] = new_value;
        }
    }

    int getNrOfValues()
    {
        return nr_of_values;
    }

    int getIntValueByIndex(int i)
    {
        return values[i].getIntContent();
    }

    float getFloatValueByIndex(int i)
    {
        return values[i].getFloatContent();
    }

    string getTextValueByIndex(int i)
    {
        return values[i].getTextContent();
    }

    friend ostream& operator<<(ostream&, Row&);
    friend istream& operator>>(istream&, Row&);

private:
    Content* values;
    int nr_of_values;
};

ostream& operator<<(ostream& o, Row& r)
{
    o << "Nr of values: "<< r.nr_of_values << endl;
    if (r.values != nullptr)
    {
        for (int i = 0; i < r.nr_of_values; i++)
        {
            o << r.values[i] << " ";
        }
        o << endl;
    }
    return o;
}

istream& operator>>(istream& i, Row& r)
{
    cout << "Nr of values for row? ";
    i >> r.nr_of_values;
    if (i.good() && r.nr_of_values > 0)
    {
        r.values = new Content[r.nr_of_values];
        for (int j = 0; j < r.nr_of_values; j++)
        {
            cout << "values[" << j << "] = ";
            i >> r.values[j];
        }
    }
    else
    {
        r.nr_of_values = 0;
        r.values = nullptr;
    }
    return i;
}

class Column
{
public:
    Column()
    {
        name = "NaN";
        size = 0;
        content_type = 0;
        default_int_content = 0;
        default_float_content = 0;
        default_text_content = "NaN";
    }

    Column(string name, int size)
    {
        this->name = name;
        this->size = size;
    }

    Column(string name, int size, int content)
    {
        this->name = name;
        this->size = size;
        this->content_type = 1;
        this->default_int_content = content;
    }

    Column(string name, int size, float content)
    {
        this->name = name;
        this->size = size;
        this->content_type = 2;
        this->default_float_content = content;
    }

    Column(string name, int size, string content)
    {
        this->name = name;
        this->size = size;
        this->content_type = 3;
        this->default_text_content = content;
    }

    Column(Column& c)
    {
        name = c.name;
        size = c.size;
        content_type = c.content_type;
        if (content_type == 1)
        {
            default_int_content = c.default_int_content;
        }
        if (content_type == 2)
        {
            default_float_content = c.default_float_content;
        }
        if (content_type == 3)
        {
            default_text_content = c.default_text_content;
        }
    }

    Column& operator=(const Column& c)
    {
        this->name = c.name;
        this->content_type = c.content_type;
        this->size = c.size;
        if (this->content_type == 1)
            this->default_int_content = c.default_int_content;
        if (this->content_type == 2)
            this->default_float_content = c.default_float_content;
        if (this->content_type == 3)
            this->default_text_content = c.default_text_content;
        return *this;
    }
    void setNewColumn(string new_column_name, string new_column_type, string new_column_size, string new_default_type)
    {
        size = stoi(new_column_size);
        name = new_column_name;
        if (new_column_type[0] == 'I')
        {
            if (!(stoi(new_default_type) >= (pow(10, size))))
            {
                content_type = 1;
                default_int_content = stoi(new_default_type);
            }
            else
            {
                cout << "Default value too big for column " << name << endl;
            }
        }
        if (new_column_type[0] == 'F')
        {
            if (!(stoi(new_default_type) >= (pow(10, size))))
            {
                content_type = 2;
                default_float_content = stof(new_default_type);
            }
            else
            {
                cout << "Default value too big for column " << name << endl;
            }
        }
        if (new_column_type[0] == 'T')
        {
            if (!(new_default_type.length() > size))
            {
                content_type = 3;
                default_text_content = new_default_type;
            }
            else
            {
                cout << "Default value too big for column " << name << endl;
            }

        }
    }

    int getColumnType()
    {
        return content_type;
    }

    int getColumnSize()
    {
        return size;
    }

    int getDefaultIntContent()
    {
        return default_int_content;
    }

    float getDefaultFloatContent()
    {
        return default_float_content;
    }

    string getDefaultTextContent()
    {
        return default_text_content;
    }

    string getColumnName()
    {
        return name;
    }

    void setName(string name)
    {
        if(name != "NaN")
            this->name = name;
    }

    void setContentType(int type)
    {
        if(type == 1 || type == 2 || type == 3)
            content_type = type;
    }

    void setSize(int size)
    {
        if(size >= 1)
            this->size = size;
    }

    void setDefaultIntContent(int int_content)
    {
        if(int_content < pow(10, size))
            default_int_content = int_content;
    }

    void setDefaultFloatContent(float float_content)
    {
        if(float_content < pow(10, size))
            default_float_content = float_content;
    }

    void setDefaultTextContent(string text_content)
    {
        if (text_content.length() <= size)
            default_text_content = text_content;
    }

    bool operator!()
    {
        return size == 0;
    }

    Column operator++()
    {
        this->size++;
        return *this;
    }

    Column operator++(int i)
    {
        Column column_copy = *this;
        this->size++;
        return column_copy;
    }

    Column operator+(int addToSize)
    {
            Column column_copy = *this;
            column_copy.size += addToSize;
            return column_copy;
    }

    int operator[](int index)
    {
        if (index == 1 && content_type == 1)
        {
            return default_int_content;
        }
        if (index == 2 && content_type == 2)
        {
            return (int)default_float_content;
        }
        if (index != 1 && index != 2)
        {
            throw exception("Bad index");
        }
        if (content_type == 0)
        {
            throw exception("Column with uninitialized content");
        }  
    }

    explicit operator int()
    {
        if(content_type == 1)
            return default_int_content;
        else 
            throw exception("Column doesn't have integer type");
    }

    bool operator>(Column c)
    {
        return this->size > c.size;
    }

    bool operator==(Column c)
    {
        return this->size == c.size && this->content_type == c.content_type;
    }

    friend ostream& operator<<(ostream&, Column&);
    friend istream& operator>>(istream&, Column&);
    
private:
    string name;
    //0 - uninitialized, 1 - int, 2 - float, 3 - string
    int content_type;
    int size;
    int default_int_content;
    float default_float_content;
    string default_text_content;
};

ostream& operator<<(ostream& o, Column& c)
{
    o << "Column name: " << c.name << "\n";
    o << "Column type: ";
    switch (c.content_type)
    {
    case 1:
        o << "integer" << '\n';
        o << "Column default content: " << c.default_int_content << "\n";
        break;
    case 2:
        o << "float" << '\n';
        o << "Column default content: " << c.default_float_content << "\n";
        break;
    case 3:
        o << "text" << '\n';
        o << "Column default content: " << c.default_text_content << "\n";
        break;
    default:
        o << "uninitialized" << "\n";
        break;
    }
    o << "Column size: " << c.size << "\n";
    return o;
}

istream& operator>>(istream& i, Column& c)
{
    cout << "Column name: ";
    i >> c.name;
    cout << "Column type (1 - int, 2 - float, 3 - text): ";
    i >> c.content_type;
    cout << "Column size: ";
    i >> c.size;
    cout << "Column default content: ";
    switch (c.content_type)
    {
    case 1:
        i >> c.default_int_content;
        while (c.default_int_content >= pow(10, c.size))
        {
            cout << "Value is too big for size " << c.size << ", try again\n";
            i >> c.default_int_content;
        }
        break;
    case 2:
        i >> c.default_float_content;
        while (c.default_float_content >= pow(10, c.size))
        {
            cout << "Value is too big for size " << c.size << ", try again\n";
            i >> c.default_float_content;
        }
        break;
    case 3:
        i >> c.default_text_content;
        while (c.default_text_content.length() >= c.size)
        {
            cout << "Value is too big for size " << c.size << ", try again\n";
            i >> c.default_text_content;
        }
        break;
    default:
        break;
    }
    return i;
}

class Table
{
public:
    Table()
    {
        name = "NaN";
        columns = nullptr;
        rows = nullptr;
        nr_of_columns = 0;
        nr_of_rows = 0;
    }

    Table(string name, int nr_of_columns, int nr_of_rows)
    {
        this->name = name;
        this->nr_of_columns = nr_of_columns;
        this->nr_of_rows = nr_of_rows;
        this->columns = nullptr;
        this->rows = nullptr;
    }

    Table(string name, int nr_of_columns, int nr_of_rows, Column* columns, Row* rows)
    {
        this->name = name;
        this->nr_of_columns = nr_of_columns;
        this->nr_of_rows = nr_of_rows;
        this->columns = columns;
        this->rows = rows;
    }

    ~Table()
    {
        if (columns != nullptr)
            delete[] columns;
        if (rows != nullptr)
            delete[] rows;
    }

    Table& operator=(const Table& t)
    {
        this->nr_of_rows = t.nr_of_rows;
        this->nr_of_columns = t.nr_of_columns;
        this->name = t.name;
        if (t.columns != nullptr && t.nr_of_columns != 0)
        {
            if (this->columns != nullptr)
                delete[] this->columns;
            this->columns = new Column[this->nr_of_columns];
            for (int i = 0; i < this->nr_of_columns; i++)
                this->columns[i] = t.columns[i];
        }
        if (t.rows != nullptr && t.nr_of_rows != 0)
        {
            if (this->rows != nullptr)
                delete[] this->rows;
            this->rows = new Row[this->nr_of_rows];
            for (int i = 0; i < this->nr_of_rows; i++)
                this->rows[i] = t.rows[i];
        }
        return *this;
    }

    bool operator!()
    {
        return nr_of_rows == 0;
    }

    Table operator++()
    {
        if (rows != nullptr && nr_of_rows != 0)
        {
            Row* rows_copy;
            rows_copy = new Row[nr_of_rows];
            for (int i = 0; i < nr_of_rows; i++)
            {
                rows_copy[i] = rows[i];
            }
            nr_of_rows++;
            delete[] rows;
            rows = new Row[nr_of_rows];
            for (int i = 0; i < nr_of_rows - 1; i++)
            {
                rows[i] = rows_copy[i];
            }
            delete[] rows_copy;
        }
        else
        {
            nr_of_rows = 1;
            rows = new Row[1];
        }
        return *this;
    }

    Table operator++(int i)
    {
        Table table_copy = *this;
        if (rows != nullptr && nr_of_rows != 0)
        {
            Row* rows_copy;
            rows_copy = new Row[nr_of_rows];
            for (int i = 0; i < nr_of_rows; i++)
            {
                rows_copy[i] = rows[i];
            }
            nr_of_rows++;
            delete[] rows;
            rows = new Row[nr_of_rows];
            for (int i = 0; i < nr_of_rows - 1; i++)
            {
                rows[i] = rows_copy[i];
            }
            delete[] rows_copy;
        }
        else
        {
            nr_of_rows = 1;
            rows = new Row[1];
        }
        return table_copy;
    }

    Table& operator+(Row r)
    {
        Table content_copy = *this;
        if (content_copy.rows != nullptr && content_copy.nr_of_rows != 0)
        {
            Row* rows_copy;
            rows_copy = new Row[content_copy.nr_of_rows];
            for (int i = 0; i < content_copy.nr_of_rows; i++)
            {
                rows_copy[i] = content_copy.rows[i];
            }
            content_copy.nr_of_rows += 1;
            delete[] content_copy.rows;
            content_copy.rows = new Row[content_copy.nr_of_rows];
            for (int i = 0; i < content_copy.nr_of_rows - 1; i++)
            {
                content_copy.rows[i] = rows_copy[i];
            }
            content_copy[nr_of_rows - 1] = r;
            delete[] rows_copy;
        }
        else
        {
            content_copy.nr_of_rows = 1;
            content_copy.rows = new Row[1];
            content_copy.rows[0] = r;
        }
        return content_copy;
    }

    Row& operator[](int index)
    {
        return rows[index];
    }

    explicit operator int()
    {
        return nr_of_rows;
    }

    bool operator>(Table t)
    {
        return nr_of_rows>t.nr_of_rows;
    }

    bool operator==(Table t)
    {
        if (nr_of_rows == t.nr_of_rows)
        {
            cout << "a";
            if (rows != nullptr)
            {
                cout << "b";
                for (int i = 0; i < nr_of_rows; i++)
                {
                    if (!(rows[i] == t.rows[i]))
                    {
                        return false;
                    }
                }
            }
            else
            {
                cout << "c";
                return true;
            }
        }
        return true;
    }

    friend ostream& operator<<(ostream&, Table&);
    friend istream& operator>>(istream&, Table&);

    void addColumn(string column_name, string column_type, string column_size, string default_type)
    {
        if (columns == nullptr || nr_of_columns == 0)
        {
            nr_of_columns = 1;
            columns = new Column[nr_of_columns];
            columns[0].setNewColumn(column_name, column_type, column_size, default_type);
        }
        else
        {
            Column* columns_copy;
            columns_copy = new Column[nr_of_columns];
            for (int i = 0; i < nr_of_columns; i++)
            {
                columns_copy[i] = columns[i];
            }
            nr_of_columns += 1;
            delete[] columns;
            columns = new Column[nr_of_columns];
            for (int i = 0; i < nr_of_columns - 1; i++)
            {
                columns[i] = columns_copy[i];
            }
            columns[nr_of_columns - 1].setNewColumn(column_name, column_type, column_size, default_type);
            delete[] columns_copy;
        }
    }

    void addRow()
    {
        if (rows == nullptr || nr_of_rows == 0)
        {
            nr_of_rows = 1;
            rows = new Row[1];
        }
        else
        {
            Row* rows_copy;
            rows_copy = new Row[nr_of_rows];
            for (int i = 0; i < nr_of_rows; i++)
            {
                rows_copy[i] = rows[i];
            }
            nr_of_rows += 1;
            delete[] rows;
            rows = new Row[nr_of_rows];
            for (int i = 0; i < nr_of_rows - 1; i++)
            {
                rows[i] = rows_copy[i];
            }
        }
    }

    void addValueToRow(Content value, int type)
    {
        this->rows[nr_of_rows - 1].addValue(value, type);
    }

    void setTableName(string table_name)
    {
        name = table_name;
    }

    int getNrOfColumns()
    {
        return nr_of_columns;
    }

    string getColumnNameByIndex(int i)
    {
        return columns[i].getColumnName();
    }

    int getColumnTypeByIndex(int i)
    {
        return columns[i].getColumnType();
    }

    bool checkSizeForColumn(int column_nr, int size)
    {
        return size <= columns[column_nr].getColumnSize();
    }

    /*void displayRows()
    {
        for(int i = 0;i < nr_of_rows;i++)
        {
            cout << "row " << i << endl;
            rows[i].getContents();
        }
    }*/

    int columnIndexByName(string column_name)
    {
        for (int i = 0; i < nr_of_columns; i++)
        {
            if (columns[i].getColumnName() == column_name)
            {
                return i;
            }
        }
        return -1;
    }

    void deleteFrom(string column_name, string value)
    {
        int column_type = this->getColumnTypeByIndex(this->columnIndexByName(column_name));
        if (rows == nullptr || nr_of_rows == 0)
        {
            cout << "Cannot delete row, there are no rows in the table " << name << "\n";
        }
        else
        {
            int deleted = 0;

            for (int i = nr_of_rows - 1; i >= 0; i--)
            {
                //cout << nr_of_rows << endl;

                if (column_type == 1)
                {
                    if (rows[i].getIntValueByIndex(this->columnIndexByName(column_name)) == stoi(value))
                    {
                        this->deleteRowByIndex(i);
                        deleted++;
                    }
                }

                if (column_type == 2)
                {
                    if (rows[i].getFloatValueByIndex(this->columnIndexByName(column_name)) == stof(value))
                    {
                        this->deleteRowByIndex(i);
                        deleted++;
                    }
                }

                if (column_type == 3)
                {
                    if (rows[i].getTextValueByIndex(this->columnIndexByName(column_name)) == value)
                    {
                        this->deleteRowByIndex(i);
                        deleted++;
                    }
                }

            }

            if (!(deleted))
            {
                cout << "No value in any row matches the value typed in clause\n";
            }
            else
            {
                cout << "Deleted " << deleted << " rows\n";
            }
        }
    }

    void deleteRowByIndex(int row_i)
    {
        if (nr_of_rows > 1)
        {
            Row* rows_copy;
            rows_copy = new Row[nr_of_rows];
            for (int i = 0; i < nr_of_rows; i++)
            {
                rows_copy[i] = rows[i];
            }
            delete[] rows;
            nr_of_rows--;
            rows = new Row[nr_of_rows];
            int i = 0;
            int j = 0;
            while (i < nr_of_rows)
            {
                if (j == row_i)
                {
                    rows[i] = rows_copy[++j];
                }
                else
                {
                    rows[i] = rows_copy[j];
                }
                i++;
                j++;
            }
            delete[] rows_copy;
            //cout << "Row deleted\n";
        }
        else
        {
            if (rows != nullptr)
            {
                delete[] rows;
            }
            nr_of_rows = 0;
            rows = nullptr;
        }
    }

    

    string getTableName()
    {
        return name;
    }
    

    void setName(string name)
    {
        this->name = name;
    }

private:
    string name;
    Column* columns;
    Row* rows;
    int nr_of_columns;
    int nr_of_rows;

};

ostream& operator<<(ostream& o, Table& t)
{
    o << "Table name: " << t.name << endl;
    o << "Columns: " << endl;
    if (t.columns != nullptr)
    {
        for (int i = 0; i < t.nr_of_columns; i++)
        {
            o << t.columns[i].getColumnName() << " ";
        }
    }
    else
    {
        o << "There are no columns in the table";
    }
    o << endl;
    if (t.rows != nullptr)
    {
        o << "Rows: " << endl;
        for (int i = 0; i < t.nr_of_rows; i++)
        {
            o << t.rows[i] << endl;
        }
    }
    else
    {
        o << "There are no rows in the table";
    }
    return o;
}
istream& operator>>(istream& i, Table& t)
{
    cout << "Table name? ";
    i >> t.name;
    cout << "Nr of columns? ";
    i >> t.nr_of_columns;
    if (t.nr_of_columns != 0)
    {
        if (t.columns != nullptr)
        {
            delete[] t.columns;
        }
        t.columns = new Column[t.nr_of_columns];
        for (int j = 0; j < t.nr_of_columns; j++)
        {
            cout << "Column " << j << ": ";
            i >> t.columns[j];
        }
    }
    cout << "Nr of rows? ";
    i >> t.nr_of_rows;
    if (t.nr_of_rows != 0)
    {
        cout << "Set the number of values for each row to the number of columns added to this table!\n";
        if (t.rows != nullptr)
        {
            delete[] t.rows;
        }
        t.rows = new Row[t.nr_of_rows];
        for (int j = 0; j < t.nr_of_rows; j++)
        {
            cout << "Row " << j << ": ";
            i >> t.rows[j];
        }
        for (int j = 0; j < t.nr_of_rows; j++)
        {
            if (t.rows[j].getNrOfValues() != t.nr_of_columns)
            {
                cout << "Error: Number of values for row " << j << "doesn't match the number of columns in the table\nOnly the table name and columns will be saved\n";
                delete[] t.rows;
                t.nr_of_rows = 0;
                break;
            }
            for (int x = 0; x < t.nr_of_columns; x++)
            {
                if (t.rows[j][x].getContentType() != t.getColumnTypeByIndex(x))
                {
                    cout << "Error: Type of value " << x << " in row " << j << " doesn't match the type of the corresponding column in the table\nOnly the table name and columns will be saved\n";
                }
            }
        }
    }
    return i;
}

class Database {

public:
    Database()
    {
        tables = nullptr;
        nr_of_tables = 0;
    }


    Database(int nr_of_tables)
    {
        this->nr_of_tables = nr_of_tables;
        this->tables = nullptr;
    }

    Database(int nr_of_tables,Table* tables)
    {
        this->nr_of_tables = nr_of_tables;
        this->tables = tables;
    }
    ~Database()
    {
        if (tables != nullptr)
            delete[] tables;
    }
    Database(Database& d)
    {
        nr_of_tables = d.nr_of_tables;
        if (nr_of_tables != 0)
        {
            tables = new Table[nr_of_tables];
            for (int i = 0; i < nr_of_tables; i++)
            {
                tables[i] = d.tables[i];
            }
        }
        else
        {
            tables = nullptr;
        }
    }

    Database& operator=(Database& c)
    {
        this->nr_of_tables = c.nr_of_tables;
        if (this->tables != nullptr)
            delete[] this->tables;
        if (c.nr_of_tables == 0 || c.tables ==  nullptr)
        {
            this->tables = nullptr;
        }
        else
        {
            this->tables = new Table[this->nr_of_tables];
            for (int i = 0; i < this->nr_of_tables; i++)
            {
                this->tables[i] = c.tables[i];
            }
        }
        return *this;
    }

    bool operator!()
    {
        return nr_of_tables == 0;
    }

    Database& operator++()
    {
            Table* tables_copy;
            tables_copy = new Table[nr_of_tables];
            for (int i = 0; i < nr_of_tables; i++)
            {
                tables_copy[i] = tables[i];
            }
            nr_of_tables += 1;
            delete[] tables;
            tables = new Table[nr_of_tables];
            for (int i = 0; i < nr_of_tables - 1; i++)
            {
                tables[i] = tables_copy[i];
            }
            delete[] tables_copy;
        return *this;
    }

    Database operator++(int i)
    {
        Database database_copy = *this;
        Table* tables_copy;
        tables_copy = new Table[nr_of_tables];
        for (int i = 0; i < nr_of_tables; i++)
        {
            tables_copy[i] = tables[i];
        }
        nr_of_tables += 1;
        delete[] tables;
        tables = new Table[nr_of_tables];
        for (int i = 0; i < nr_of_tables - 1; i++)
        {
            tables[i] = tables_copy[i];
        }
        delete[] tables_copy;
        return database_copy;
    }

   Database& operator+(Table t)
    {
        Database database_copy = *this;
        if (database_copy.nr_of_tables != 0 && database_copy.tables != nullptr)
        {
            Table* tables_copy;
            tables_copy = new Table[database_copy.nr_of_tables];
            for (int i = 0; i < database_copy.nr_of_tables; i++)
            {
                tables_copy[i] = database_copy.tables[i];
            }
            database_copy.nr_of_tables++;
            if (database_copy.tables != nullptr)
            {
                delete[] database_copy.tables;
            }
            database_copy.tables = new Table[database_copy.nr_of_tables];
            for (int i = 0; i < database_copy.nr_of_tables-1; i++)
            {
                database_copy.tables[i] = tables_copy[i];
            }
            database_copy.tables[nr_of_tables - 1] = t;
        }
        else
        {
            database_copy.nr_of_tables = 1;
            database_copy.tables = new Table[database_copy.nr_of_tables];
            database_copy.tables[0] = t;
        }
        return database_copy;
    }

    Table& operator[](int index)
    {
        if (nr_of_tables > index)
        {
            return tables[index];
        }
    }

    explicit operator int()
    {
        return nr_of_tables;
    }

    bool operator>(Database d)
    {
        return this->nr_of_tables > d.nr_of_tables;
    }

    bool operator==(Database d)
    {
        return this->nr_of_tables == d.nr_of_tables;
    }

    void createTable(string new_table_name)
    {
        if (tables == nullptr || nr_of_tables == 0)
        {
            nr_of_tables = 1;
            tables = new Table[nr_of_tables];
            tables[0].setTableName(new_table_name);
        }
        else
        {
            Table* tables_copy;
            tables_copy = new Table[nr_of_tables];
            for (int i = 0; i < nr_of_tables; i++)
            {
                tables_copy[i] = tables[i];
            }
            nr_of_tables += 1;
            delete[] tables;
            tables = new Table[nr_of_tables];
            for (int i = 0; i < nr_of_tables - 1; i++)
            {
                tables[i] = tables_copy[i];
            }
            tables[nr_of_tables - 1].setName(new_table_name);
            delete[] tables_copy;
        }
    }

    void addColumnToTable(string table_name, string column_name, string column_type, string column_size, string default_type)
    {
        //for(int i=0;i<nr_of_tables;i++)
        //{

            //if(tables[i].getTableName() == table_name)
           // {    
        tables[this->findIndexOfTable(table_name)].addColumn(column_name, column_type, column_size, default_type);
        //  break;
    //  }
 // }
    }

    Table& getTable(string table_name)
    {
        return this->tables[this->findIndexOfTable(table_name)];
    }

    void getTables()
    {
        for (int i = 0; i < nr_of_tables; i++)
        {
            cout << tables[i].getTableName() << endl;
        }
    }

    int findIndexOfTable(string table_name)
    {
        for (int i = 0; i < nr_of_tables; i++)
        {
            if (tables[i].getTableName() == table_name)
            {
                return i;
            }
        }
        return -1;
    }

    int getColumnTypeForTableByIndex(string table_name, int i)
    {
        return tables[this->findIndexOfTable(table_name)].getColumnTypeByIndex(i);
    }

    int getNrOfColumnsOfTable(string table_name)
    {
        return tables[this->findIndexOfTable(table_name)].getNrOfColumns();
    }
    void dropTable(string table_to_drop)
    {
        if (tables == nullptr || nr_of_tables == 0)
        {
            cout << "Cannot delete table " << table_to_drop << ", there are no tables in the database\n";
        }
        else
        {
            Table* tables_copy;
            tables_copy = new Table[nr_of_tables];
            for (int i = 0; i < nr_of_tables; i++)
            {
                tables_copy[i] = tables[i];
            }
            delete[] tables;
            //cout << "nr tabele: " << nr_of_tables << endl;
            nr_of_tables--;
            tables = new Table[nr_of_tables];
            int i = 0;
            int j = 0;
            while (i < nr_of_tables)
            {
                if (table_to_drop == tables_copy[j].getTableName())
                {
                    tables[i] = tables_copy[++j];
                }
                else
                {
                    tables[i] = tables_copy[j];
                }
                i++;
                j++;
            }
            delete[] tables_copy;
            cout << "Table " << table_to_drop << " dropped\n";
        }
    }

    friend ostream& operator<<(ostream&, Database&);
    friend istream& operator>>(istream&, Database&);

private:
    Table* tables;
    int nr_of_tables;
};

ostream& operator<<(ostream& o, Database& d)
{
    o << "Nr of tables in database: " << d.nr_of_tables;
    if (d.nr_of_tables > 0)
    {
        for (int i = 0; i < d.nr_of_tables; i++)
        {
            o << d.tables[i] << endl;
        }
    }
    return o;
}

istream& operator>>(istream& i, Database& d)
{
    cout << "Nr of tables in database? ";
    i >> d.nr_of_tables;
    if (d.nr_of_tables > 0)
    {
        if (d.tables != nullptr)
        {
            delete[] d.tables;
        }
        d.tables = new Table[d.nr_of_tables];
        for (int j = 0; j < d.nr_of_tables; j++)
        {
            i >> d.tables[j];
        }
    }
    return i;
}
