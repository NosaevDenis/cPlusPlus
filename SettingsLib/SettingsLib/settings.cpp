//
//  main.cpp
//  settingsLib
//
//  Created by Денис on 17.05.15.
//  Copyright (c) 2015 Денис. All rights reserved.
//


#include "settings.h"


int main(int argc, char* argv[])
{
    return 0;
}



settings::settings(std::string const & filename)
{
    this->filename = filename;
    this->reload();
}

void settings::reload()
{
    char *ch = new char[this->filename.length() + 1];
    strcpy(ch, this->filename.c_str());
    this->par.clear();
    string s,s1;
    std::ifstream input(ch);
    while (getline(input, s)) {
        getline(input, s1);
        this->par[s]=s1;
    };
    input.close();
};

string const & settings::get(std::string const & name, std::string const & def) const {
   return ((par.find(name)!=par.end()) ?  par.find(name)->second : def );
    
}

settings::param & settings::param::operator/=(int value) {
    stringstream ss;
    int d=atoi(this->value.c_str()) / value;
    ss << d;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator/=(double value) {
    double temp=::atof(this->value.c_str());
    temp=temp/value;
    ostringstream ss;
    ss << temp;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator|=(bool value) {
    if(value){this->value="true";};
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator&=(bool value) {
    if(!value){this->value="false";};
    parent->set(this->name, this->value);
    return *this;
}

void settings::set(std::string const & name,std::string const & value)
{
    this->par[name]=value;
    char* ch=new char[filename.length() + 1];
    strcpy(ch, filename.c_str());

    std::ofstream output(ch);
    map<string, string>::iterator it;
    for(it=par.begin() ; it != par.end(); it++){
        output << (*it).first << endl;
        output <<(*it).second << endl;
    }
    output.close();
}

void settings::reset() {
    char *ch = new char[filename.length() + 1];
    strcpy(ch, filename.c_str());
    ofstream(ch, std::ofstream::trunc);
    par.clear();
}

settings::param::param(const string & name, std::string value, const settings *parent) {
    this->value = value;
    this->name = name;
    this->parent = const_cast<settings* const>(parent);
}

settings::param::operator std::string() const {
    return string(value);
}

settings::param::operator bool() const {
    return (value == "true");
}
settings::param::operator int() const {
    return atoi(value.c_str());
}
settings::param::operator double() const {
    
    double temp=::atof(value.c_str());
    return temp;
}
settings::param & settings::param::operator=(char const * value) {
    return this->operator=(std::string(value));
}
settings::param & settings::param::operator=(std::string const & value) {
    
    this->value = value;
    parent->set(this->name, this->value);
    return *this;
}
settings::param & settings::param::operator=(int value) {
    stringstream ss;
    ss << value;
    this->value = ss.str();
    
    
    parent->set(this->name, this->value);
    return *this;
}
settings::param & settings::param::operator=(bool value) {
    ostringstream ss;
    ss << boolalpha << value;
    
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}
settings::param & settings::param::operator=(double value) {
    ostringstream ss;
    ss << value;
    
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator+=(std::string const & value) {
    this->value += value;
    parent->set(this->name, this->value);
    return *this;
}
settings::param & settings::param::operator+=(int value) {
    
    stringstream ss;
    int d=atoi(this->value.c_str()) + value;
    ss << d;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator+=(double value) {
    
    double temp=::atof(this->value.c_str());
    temp=temp+value;
    ostringstream ss;
    ss << temp;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator-=(int value) {
    stringstream ss;
    int d=atoi(this->value.c_str()) - value;
    ss << d;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator-=(double value) {
    double temp=::atof(this->value.c_str());
    temp=temp-value;
    ostringstream ss;
    ss << temp;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator*=(int value) {
    stringstream ss;
    int d=atoi(this->value.c_str()) * value;
    ss << d;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator*=(double value) {
    double temp=::atof(this->value.c_str());
    temp=temp*value;
    ostringstream ss;
    ss << temp;
    this->value = ss.str();
    parent->set(this->name, this->value);
    return *this;
}

bool settings::param::is_empty() const {
    return this->value.empty();
}

const settings::param settings::operator[](std::string const &name) const {
    return param(name, par.find(name)->second, this);
}

settings::param settings::operator[](std::string const & name) {
    return param(name, par.find(name)->second, this);
}

