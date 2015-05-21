//
//  main.cpp
//  settingsTest
//
//  Created by Денис on 20.05.15.
//  Copyright (c) 2015 Денис. All rights reserved.
//

# include <random>
# include <string>
# include <QString>
# include "settings.h"
# include <QTest>

class SettingsTest :
public QObject{
    Q_OBJECT
    public :
    SettingsTest() {}
    private Q_SLOTS :
    
    void init() {
        settings set("input.txt");
        set.reset();
        set.reload();
    }
    
    void get_set() {
        settings set("input.txt");
        set.set("aaaaaaa", "bbb");
        QCOMPARE(set.get("aaaaaaa"), string("bbb"));
        set.set("ddd", "trtrtr");
        QCOMPARE(set.get("ddd"), string("trtrtr"));
        QCOMPARE(set.get("rarara", string("ooo111")), string("ooo111"));
        set.set("123123", string("111"));
        QCOMPARE(set.get("123123", "555"), string("111"));
        set.set("wthwrthwrth", string("trtwhipwijrt"));
        QCOMPARE(set.get("wthwrthwrth", "123123123123123"), string("trtwhipwijrt"));
        set.set("tetete", string("ololo"));
        QCOMPARE(set.get("tetete", "hhhhhhh"), string("ololo"));
    }
    void reset_reload()
    {
    settings set("input.txt");
    set.set("aaa", "bbb");
    set.reload();
    QCOMPARE(set.get("aaa"), string("bbb"));
    set.reset();
    QCOMPARE(set.get("aaa"), string(""));
    }
    
    void rand() {
        settings set("input.txt");
        std::mt19937_64 r;
        long long a[100];
        for (int i = 1; i < 100; i++) {
            a[i] = r();
            set.set("bbbd" + to_string(i), to_string(a[i]));
        }
        for (int i = 1; i < 100; i++) {
            QCOMPARE(set.get("bbbd" + to_string(i), "ttt"), to_string(a[i]));
        }
    }
    void bonus(){
        settings set("input.txt");
        set["11"]="ggg";
        set["ggg"]="11";
        set["hh"]="ttt";
        set["rrr"]="222";
        set["ddd"]="444";
        set["44"]="gggaa";
        set["333"]="tttab";
        set["lalala"]="yyy";
        
        set["opa"]="na";
        set.reload();
        
        QCOMPARE(set.get("11"), string("ggg"));
        QCOMPARE(set.get("ggg"), string("11"));
        QCOMPARE(set.get("hh"), string("ttt"));
        QCOMPARE(set.get("rrr"), string("222"));
        QCOMPARE(set.get("ddd"), string("444"));
        QCOMPARE(set.get("44"), string("gggaa"));
        QCOMPARE(set.get("333"), string("tttab"));
        QCOMPARE(set.get("lalala"), string("yyy"));
        QCOMPARE(set.get("opa"), string("na"));
        
        set.reset();
        
        QCOMPARE(set.get("11"), string(""));
        QCOMPARE(set.get("ggg"), string(""));
        QCOMPARE(set.get("hh"), string(""));
        QCOMPARE(set.get("rrr"), string(""));
        QCOMPARE(set.get("ddd"), string(""));
        QCOMPARE(set.get("44"), string(""));
        QCOMPARE(set.get("333"), string(""));
        QCOMPARE(set.get("lalala"), string(""));
        QCOMPARE(set.get("opa"), string(""));
        
    }
};

QTEST_APPLESS_MAIN(SettingsTest);

#include "settingsTest.moc"