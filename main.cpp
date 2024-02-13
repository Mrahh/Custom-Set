#include <iostream>
#include "set.hpp"
#include <sstream>      
struct equal_int {
  bool operator()(int a, int b) const {
    return a==b;
  }
};

struct is_even {
  bool operator()(int a) const {
    return a%2 == 0;
  }
};


struct is_bigger_than_10 {
  bool operator()(int a) const {
    return a > 10;
  }
};


struct is_decrescent {
  bool operator()(int a, int b) const {
    return a > b;
  }
};


struct str_size_bigger_than_5 {
  bool operator()(std::string a) const {
    return a.size() > 5;
  }
};


void test_stringhe() {
  std::cout << "Inizio test stringhe" << std::endl;

  set<std::string, std::equal_to<std::string>> s1;
  set<std::string, std::equal_to<std::string>> s2;

  assert(s1.add("str1"));
  assert(s1.add("str2"));
  assert(s1.add("str3"));

  assert(s1.contains("str1"));
  assert(s1.contains("str3"));
  assert(!s1.contains("str2342"));

  assert(!s1.add("str1"));
  assert(s1.add("str4"));

  assert(s1.remove("str4"));
  assert(!s1.remove("str4"));
  assert(s1.remove("str1"));

  std::cout << "  s1: " << s1 << std::endl;
  std::cout << "  s1[0]: " << s1[0] << std::endl;
  std::cout << "  s1[1]: " << s1[1] << std::endl;
  std::cout << "Passati test stringhe OK" << std::endl;
}


void test_interi() {
    std::cout << "Inizio test interi..." << std::endl;
    // test della classe set
    set<int, equal_int> s1;
    set<int, equal_int> s2;
    
    assert(s1.add(1));
    assert(s1.add(2));
    assert(s1.add(3));

    assert(s1.contains(1));
    assert(!s1.contains(523));

    assert(!s1.add(2));
    assert(!s1.add(3));

    assert(s1[0] == 1);
    assert(s1[1] == 2);
    assert(s1[2] == 3);

    assert(s1.remove(1));
    assert(s1.remove(2));
    assert(!s1.remove(324));

    assert(s1[0] == 3);

  std::cout << "Passati test interi OK" << std::endl;

}


void test_operatori() {
  std::cout << "Inizio test operatori..." << std::endl;
  
  set<std::string, std::equal_to<std::string>> s1;
  set<std::string, std::equal_to<std::string>> s2;

  
  assert(s1.add("str1"));
  assert(s1.add("str2"));
  assert(s1.add("str3"));
  assert(s1.add("str4"));
  assert(s1.add("str5"));
  assert(!s1.add("str1"));

  assert(s2.add("str6"));
  assert(s2.add("str7"));
  assert(s2.add("str8"));
  assert(s2.add("str9"));
  assert(s2.add("str10"));
  assert(s2.add("str1"));
  assert(s2.add("str3"));
  assert(s2.add("str2"));

  assert(s1.remove("str5"));
  assert(s1.remove("str2"));
  assert(s1.remove("str4"));
  assert(!s1.remove("stringa che non esiste"));
  assert(s2.remove("str2"));

  assert(s1.add("str2"));

  std::cout << "  s1:"  << s1 << std::endl;
  std::cout << "  s2:"  << s2 << std::endl;

  std::cout << "  test stampa con operator+" << (s1+s2) << std::endl;

  std::cout << "  test stampa con operator-" << (s1-s2) << std::endl;

  s1.empty();

  std::cout << "  svuotato s1: " << s1 << std::endl;

  std::cout << "  test stampa con operator+" << (s1+s2) << std::endl;

  std::cout << "  test stampa con operator-" << (s1-s2) << std::endl;
  std::cout << "Passati test operatori OK" << std::endl;

}


void test_filter() {
  std::cout << "Inizio test filter..." << std::endl;
  set<int, equal_int> s1;

  assert(s1.add(1));
  assert(s1.add(2));
  assert(s1.add(3));
  assert(s1.add(4));
  assert(s1.add(10));
  assert(s1.add(123));
  assert(s1.add(1234));
  assert(s1.add(155));

  std::cout << "  stampa tutti elementi: " << s1 << std::endl;
  std::cout << "  stampa elementi pari: " << filter_out(s1, is_even()) << std::endl;;

  set<std::string, std::equal_to<std::string>> s2;

  assert(s2.add("stringagrande"));
  assert(s2.add("str"));
  assert(s2.add("stringona"));
  assert(s2.add("str2"));

  std::cout << "  stampa tutti elementi: " << s2 << std::endl;
  std::cout << "  stampa elementi len > 5: " << filter_out(s2, str_size_bigger_than_5()) << std::endl;

  std::cout << "Passati test filter OK" << std::endl;
}


void test_file() {
  std::cout << "Inizio test file..." << std::endl;
  set<std::string, std::equal_to<std::string>> s1;

  assert(s1.add("romolo"));
  assert(s1.add("numa pompilio"));
  assert(s1.add("tullo ostilio"));
  assert(s1.add("anco marzio"));
  assert(s1.add("tarquinio prisco"));
  assert(s1.add("servio tullio"));
  assert(s1.add("tarquinio il superbo"));
  assert(s1.add("bruto"));
  assert(s1.add("colatino"));

  std::cout << "  s1: " << s1 << std::endl;

  save(s1, "file.txt");

  std::ifstream file("file.txt");
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

 
  std::string expectedOutput;
  expectedOutput = "9 (romolo) (numa pompilio) (tullo ostilio) (anco marzio) (tarquinio prisco) (servio tullio) (tarquinio il superbo) (bruto) (colatino)";

  // Verifica il contenuto del file sia uguale alla stringa che ci si aspetta
  assert(buffer.str() == expectedOutput);

  std::cout << "Passati test file OK" << std::endl;

}


void test_uguale() {
  std::cout << "Inizio test uguale..." << std::endl;

  set<int, equal_int> s1;
  set<int, equal_int> s2;

  assert(s1.add(1));
  assert(s1.add(2));
  assert(s1.add(3));
  assert(s1.add(4));
  assert(s1.add(5));
  assert(s1.add(6));
  assert(s1.add(7));
  assert(s1.add(8));
  assert(s1.add(9));

  assert(s2.add(1));
  assert(s2.add(2));
  assert(s2.add(3));
  assert(s2.add(4));
  assert(s2.add(5));
  assert(s2.add(6));
  assert(s2.add(7));
  assert(s2.add(8));
  assert(s2.add(9));


  assert(s1 == s2);
  
  assert(s1.remove(1));
  assert(!(s1 == s2));

  assert(s1.remove(2));
  assert(s1.remove(3));
  assert(s1.remove(4));
  assert(s1.remove(5));
  assert(s1.remove(6));
  assert(s1.remove(7));
  assert(s1.remove(8));
  assert(s1.remove(9));

  assert(s2.remove(1));
  assert(s2.remove(2));
  assert(s2.remove(3));
  assert(s2.remove(4));
  assert(s2.remove(5));
  assert(s2.remove(6));
  assert(s2.remove(7));
  assert(s2.remove(8));
  assert(s2.remove(9));
  // s1 ed s2 svuotati 

  assert(s1 == s2);

  std::cout << "Passati test uguale OK" << std::endl;

}


void test_uguale2() {
  std::cout << "Inizio test uguale2..." << std::endl;

  set<int, equal_int> s1;
  set<int, equal_int> s2;

  assert(s1.add(1));
  assert(s1.add(2));
  assert(s1.add(3));

  assert(s2.add(1));
  assert(s2.add(2));

  std::cout << "  s1: " << s1 << std::endl;
  std::cout << "  s2: " << s2 << std::endl;

  std::cout << "  scambio s1 -> s2, s2 diventa: " << (s1 = s2) << std::endl;

  std::cout << "  s1: " << s1 << std::endl;
  std::cout << "  s2: " << s2 << std::endl;

  set<int, equal_int> s3(s1);
  std::cout << "  copy constructor s3 di s1: " << s3 << std::endl;
  std::cout << "  Passati test uguale2 OK" << std::endl;

}


void test_costIter() {
  std::cout << "Inizio test costIter..." << std::endl;

  set<int, equal_int> s1;

  assert(s1.add(1));
  assert(s1.add(2));
  assert(s1.add(3));
  assert(s1.add(4));
  assert(s1.add(5));
  assert(s1.add(6));
  assert(s1.add(7));
  assert(s1.add(8));
  assert(s1.add(9));

  std::cout << "  s1: " << s1 << std::endl;
  set<int, equal_int>::const_iterator it = s1.begin();
  
  it++;
  it++;
  it++;
  it++;
  set<int, equal_int>::const_iterator it2 = s1.end();

  std::cout << "  creo un nuovo set con inizio set1 incrementato 4 volte con ++ e la fine e stampo" << std::endl;
  set<int, equal_int> set2(it, it2);
  std::cout << "  " << set2 << std::endl;

  std::cout << "Passati test costIter OK" << std::endl;

}


void test_operator2() {
  std::cout << "Inizio test operatori2..." << std::endl;

  set<int, equal_int> s1;
  set<int, equal_int> s2;
  set<int, equal_int> s3;

  assert(s1.add(1));  
  assert(s1.add(2));
  assert(s1.add(3));
  assert(s1.add(4));
  assert(s1.add(5));

  assert(s2.add(4));
  assert(s2.add(5));
  assert(s2.add(6));
  assert(s2.add(7));

  assert(s3.add(5));
  assert(s3.add(7));
  assert(s3.add(8));
  assert(s3.add(9));
  assert(s3.add(10));

  std::cout << "  (s1 + s2 + s3): " << (s1 + s2 + s3) << std::endl;

  std::cout << "  (s1 + s2 + s3 - s1): " << (s1 + s2 + s3 - s1) << std::endl;
  
  std::cout << "  (s1 - s2): " << (s1 - s2) << std::endl;

  std::cout << "  (s1 + s2 + s3 - s1 - s2 - s3): " << s1 + s2 + s3 - s1 - s2 - s3 << std::endl;

  std::cout << "Passati test operatori2 OK" << std::endl;


}


class dipinto {
  std::string _scuola, _autore, _titolo, _data, _sala;

public:

  dipinto() : _scuola(""), _autore(""), _titolo(""), _data(""), _sala("") {}

  dipinto(std::string scuola, std::string autore, std::string titolo, std::string data, std::string sala) : _scuola(scuola), _autore(autore), _titolo(titolo), _data(data), _sala(sala) {}

  
  struct ricerca_titolo {
    std::string title;

    ricerca_titolo(const std::string &titolo) : title(titolo) {}

    bool operator()(dipinto d1) const
    {
      return d1._titolo == title;
    }
  };

  struct equal_dipinto {
    bool operator()(dipinto d1, dipinto d2) const {
      return d1._titolo == d2._titolo && d1._autore == d2._autore && d1._scuola == d2._scuola && d1._data == d2._data && d1._sala == d2._sala;
    }
  };

  friend std::ostream& operator<<(std::ostream& os, const dipinto& d) {
    os << d._scuola << " " << d._autore << " " << d._titolo << " " << d._data << " " << d._sala;
    return os;
  }
};

// test con classe 
void test_classe() {
  std::cout << "Inizio test classe..." << std::endl;

  set<dipinto, dipinto::equal_dipinto> s1;
  set<dipinto, dipinto::equal_dipinto> s2;
  set<dipinto, dipinto::equal_dipinto> s3;

  dipinto d1 = dipinto(std::string("s1"), std::string("a1"), std::string("t1"), std::string("d1"), std::string("s1"));
  dipinto d2 = dipinto(std::string("s2"), std::string("a2"), std::string("t2"), std::string("d2"), std::string("s2"));
  dipinto d3 = dipinto(std::string("s3"), std::string("a3"), std::string("t3"), std::string("d3"), std::string("s3"));
  dipinto d4 = dipinto(std::string("s4"), std::string("a4"), std::string("t4"), std::string("d4"), std::string("s4"));
  dipinto d5 = dipinto(std::string("s5"), std::string("a5"), std::string("t5"), std::string("d5"), std::string("s5"));
  dipinto d6 = dipinto(std::string("s6"), std::string("a6"), std::string("t1"), std::string("d6"), std::string("s6"));

  assert(s1.add(d1));
  assert(s1.add(d2));
  assert(s1.add(d3));
  assert(s1.add(d4));
  assert(!s1.add(d1));
  assert(s1.remove(d1));
  assert(!s1.remove(d1));

  assert(s2.add(d1));
  assert(s2.add(d2));
  assert(s2.add(d3));
  assert(s2.add(d4));
  assert(s2.remove(d1));

  assert(s1 == s2);
  
  assert(s1.add(d6));
  assert(s1.add(d1));
  assert(s1.add(d5));

  assert(s3.add(d6));

  std::cout << "  s1: " << s1 << std::endl;
  std::cout << "  s2: " << s2 << std::endl;

  // test
  std::cout << "  s1 + s2: " << (s1 + s2) << std::endl;
  std::cout << "  s1 - s2: " << (s1 - s2) << std::endl;
  std::cout << "  s1 + s3: " << (s1 + s3) << std::endl;
  std::cout << "  s1 - s3: " << (s1 - s3) << std::endl;
  
  std::cout << "  ricerca dipinti con titolo 't1' " << std::endl;

  std::cout << "  " << filter_out(s1, dipinto::ricerca_titolo(std::string("t1"))) << std::endl;

  std::cout << "Passati test classe OK" << std::endl;
}


struct persona {
  std::string _nome, _cognome;
  int _eta;

  persona() : _nome(""), _cognome(""), _eta(0) {}

  persona(std::string nome, std::string cognome, int eta) : _nome(nome), _cognome(cognome), _eta(eta) {}

    struct ricerca_persona {
    std::string name;

    ricerca_persona(const std::string &nome) : name(nome) {}

    bool operator()(persona d1) const
    {
      return d1._nome == name;
    }
  };

  struct equal_persona {
    bool operator()(persona p1, persona p2) const {
      return p1._nome == p2._nome && p1._cognome == p2._cognome && p1._eta == p2._eta;
    }
  };

  friend std::ostream &operator<<(std::ostream &os, const persona &p) {
    os << p._nome << " " << p._cognome << " " << p._eta;
    return os;
  }
};


void test_struct() {
  std::cout << "Inizio test struct..." << std::endl;

  set<persona, persona::equal_persona> s1;
  set<persona, persona::equal_persona> s2;
  set<persona, persona::equal_persona> s3;

  persona p1 = persona(std::string("n1"), std::string("c1"), 1);
  persona p2 = persona(std::string("n2"), std::string("c2"), 2);
  persona p3 = persona(std::string("n3"), std::string("c3"), 3);
  persona p4 = persona(std::string("n4"), std::string("c4"), 4);
  persona p5 = persona(std::string("n5"), std::string("c5"), 5);
  persona p6 = persona(std::string("n6"), std::string("c6"), 6);
  persona p7 = persona(std::string("n1"), std::string("c7"), 7);


  assert(s1.add(p1));
  assert(s1.add(p2));
  assert(s1.add(p3));
  assert(s1.add(p4));
  assert(!s1.add(p1));
  assert(s1.remove(p1));
  assert(!s1.remove(p1));

  assert(s2.add(p1));
  assert(s2.add(p2));
  assert(s2.add(p3));
  assert(s2.add(p4));
  assert(s2.remove(p1));

  assert(s1 == s2);

  assert(s1.add(p6));
  assert(s1.add(p1));
  assert(s1.add(p5));
  assert(s1.add(p7));

  assert(s3.add(p6));


  std::cout << "  s1: " << s1 << std::endl;
  std::cout << "  s2: " << s2 << std::endl;
  std::cout << "  s3: " << s3 << std::endl;

  std::cout << "  s1 + s2: " << (s1 + s2) << std::endl;
  std::cout << "  s1 - s2: " << (s1 - s2) << std::endl;
  std::cout << "  s1 + s3: " << (s1 + s3) << std::endl;
  std::cout << "  s1 - s3: " << (s1 - s3) << std::endl;

  
  std::cout << "  ricerca persona con titolo 'n1' " << std::endl;
  std::cout << "  " << filter_out(s1, persona::ricerca_persona(std::string("n1"))) << std::endl;

  std::cout << "Passati test struct OK" << std::endl;
}


void test_part() {
    std::cout << "Inizio test part..." << std::endl;

    // Test costruttore di default e operazioni fondamentali
    set<int, std::equal_to<int>> s1;
    assert(s1.begin() == s1.end());
    assert(s1.getNumElements() == 0);

    // Test aggiunta di elementi e controllo presenza
    s1.add(5);
    s1.add(10);
    s1.add(15);
    assert(s1.contains(5));
    assert(s1.contains(10));
    assert(s1.contains(15));
    assert(!s1.contains(20));

    // Test rimozione di elementi e controllo presenza
    s1.remove(10);
    assert(!s1.contains(10));
    assert(s1.contains(5));
    assert(s1.contains(15));

    // Test operatore di assegnamento
    set<int, std::equal_to<int>> s2;
    s2 = s1;
    assert(s2.contains(5));
    assert(s2.contains(15));
    assert(!s2.contains(10));

    // Test unione di set
    set<int, std::equal_to<int>> s3;
    s3.add(15);
    s3.add(20);
    set<int, std::equal_to<int>> s4 = s1 + s3;
    assert(s4.contains(5));
    assert(s4.contains(15));
    assert(s4.contains(20));

    // Test intersezione di set
    set<int, std::equal_to<int>> s5 = s4 - s1;
    assert(s5.contains(5));
    assert(s5.contains(15));
    assert(!s5.contains(20));

    // Test iteratore
    set<int, std::equal_to<int>>::const_iterator it = s1.begin();
    assert(*it == 5);
    ++it;
    assert(*it == 15);
    ++it;
    assert(it == s1.end());
    
    std::cout << "Passati test part OK" << std::endl;


}


void test_part2(){
    std::cout << "Passati test part2..." << std::endl;

    // Test di unione con set vuoto
    set<int, std::equal_to<int>> s1;
    s1.add(5);
    s1.add(10);
    set<int, std::equal_to<int>> s2;
    set<int, std::equal_to<int>> s3 = s1 + s2;
    assert(s3.contains(5));
    assert(s3.contains(10));

    // Test di unione con set completamente sovrapposto
    set<int, std::equal_to<int>> s5 = s1 + s1;
    assert(s5.contains(5));
    assert(s5.contains(10));

    // Test di iteratore su set vuoto
    set<std::string, std::equal_to<std::string>> s6;
    set<std::string, std::equal_to<std::string>>::const_iterator it = s6.begin();
    assert(it == s6.end());

    // Test di iteratore inizializzato da due iteratori inizio e fine
    set<int, std::equal_to<int>> s8(s5.begin(), s5.end());
    assert(s8.contains(5));
    assert(s8.contains(10));
    assert(s8.getNumElements() == 2);

    std::cout << "Passati test part2 OK" << std::endl;

}


void test_set_operations() {
    std::cout << "Inizio test operazioni..." << std::endl;

    // Test di rimozione da un set vuoto
    set<int, std::equal_to<int>> s1;
    assert(!s1.remove(5));

    // Test di unione con set di dimensioni diverse
    set<int, std::equal_to<int>> s3;
    s3.add(5);
    s3.add(10);
    s3.add(15);
    set<int, std::equal_to<int>> s4;
    s4.add(10);
    set<int, std::equal_to<int>> s5 = s3 + s4;
    assert(s5.contains(5));
    assert(s5.contains(10));
    assert(s5.contains(15));

    std::cout << "Passati test operazioni OK" << std::endl;
}


void test_exceptions() {
    std::cout << "Inizio test eccezioni..." << std::endl;

    set<int, std::equal_to<int>> emptySet;

    // Test rimozione da un set vuoto
    assert(!emptySet.remove(42));

    std::cout << "Test eccezioni OK" << std::endl;
}


void test_copy_deep() {
    std::cout << "Inizio test copia profonda..." << std::endl;

    set<std::string, std::equal_to<std::string>> s1;
    s1.add("one");
    s1.add("two");

    // Copia profonda di set
    set<std::string, std::equal_to<std::string>> s2 = s1;

    // Modifica s1 e verifica che s2 rimanga invariato
    s1.remove("one");

    assert(s1.contains("two"));
    assert(!s1.contains("one"));

    assert(s2.contains("one"));
    assert(s2.contains("two"));

    std::cout << "Test copia profonda OK" << std::endl;
}


int main() {
  
  test_interi();

  test_stringhe();

  test_operatori();

  test_filter();

  test_file();

  test_uguale();

  test_uguale2();

  test_costIter();

  test_operator2();

  test_struct();

  test_classe();

  test_part();

  test_part2();

  test_set_operations();

  test_exceptions();
  
  test_copy_deep();

  std::cout << "Passati tutti i test OK" << std::endl;

  return 0;
}