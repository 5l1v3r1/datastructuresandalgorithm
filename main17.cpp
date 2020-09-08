#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using namespace std;

//düðüm tanýmý
class node
{
	public:
		double numara;
		char* ad;
		char* soyad;
		char* bolum;
		char* alinanDers;
		node* sonraki;
		node* onceki;
		
	//B+ aðacýnýn attributeleri
	vector<double> Keys;
	node *Parent;
  	bool isLeaf;
};

//Liste Tanýmý ve Fonksiyonlarý
class List
{
	public:
       List(void){head = 0; last = NULL;} //  constructor
       ~List(void); //  destructor
	     bool IsEmpty()
          {
           return head == NULL;
          }
        //Baðlantýlý listede tutulan düðümler üzerinde yapýlan iþlemler
		node* insertNode(int index,double numara,char* ad,char* soyad,char* bolum);
		int findNode(double veri);
		int deleteNode(double veri);
		void displayList(void);
	private:
		node* head;
		node*last;
};
//2. liste tanýmý ve fonksiyonlarý
class List2
{
	public:
		List2(void)
		{
			head=0;
			last=NULL;
		}
		~List2(void);
		bool IsEmpty()
		{
			return head == NULL;
		}
		//List2'de kullanýlacak fonksiyonlarýmýz
		node* dersEkle(int index,double numara,char* ad,char* soyad,char* bolum,char* alinanDers);
		int dersSil(double input);
		int dersArama(double input);
		void sadeceProgramlamaDersi(void);
		void programlamaDersiAGrubu(void);
		void programlamaDersiBGrubu(void);
		void displayList2(void);
		void heapify(int dizi[],int n,int i);
		void kumelemeSiralama(int dizi[],int n);
		private:
			node* head;
			node* last;
};

//Listeye numara, ad, soyad, bolum girdisi alarak eleman ekleme
node* List::insertNode(int index,double numara,char* ad,char* soyad,char* bolum)
{
	//Eðer index 0'dan küçükse NULL deðerini dönderir
	if(index<0)
		return NULL;
	int currIndex=1;
	node* currNode=head;
	while(currNode&&index>currIndex)
	{
		currNode = currNode->sonraki;
		currIndex++;
	}
	if(index >0&&currNode==0)
	return 0;
	//Düðümdeki verileri parametrelere eþitliyoruz.
	node* newNode = new node;
	newNode->numara=numara;
	newNode->ad=ad;
	newNode->soyad=soyad;
	newNode->bolum=bolum;
	
	if(index==0)
	{
		newNode->sonraki=head;
		last=head=newNode;
		newNode->onceki=NULL;
	}
	else
	{
		newNode->sonraki=currNode->sonraki;
		currNode->sonraki=newNode;
		newNode->onceki=currNode;
		last=newNode;
	}
	return newNode;
}

//Listeden alýnan ogrenci numarasýna göre öðrenciyi bulup indeksini döndürme
int List::findNode(double input)
{
	node* currNode=head;
	int currIndex=1;
	while(currNode && currNode->numara!=input)
	{
		currNode=currNode->sonraki;
		currIndex++;
	}
	//Öðrenci numarasý düðümlerdeki numaralarýn herhangi birine eþit ise indexinin dönderir
	if(currNode)
	return currIndex;
	//Öðrenci numarasý düðümlerdeki numaralarýn herhangi birine eþit deðil ise 0 deðerini dönderir.
	return 0;
}

//Öðrencinini numarasýný girdi olarak alýr ve düðümleri teker teker gezer,
//eðer o düðüm bulunursa düðümü siler ve adreslerini(önceki ve sonraki) deðiþtirir.
int List::deleteNode(double input)
{
	node* prevNode=NULL;
	node* currNode=head;
	int currIndex=1;
	while(currNode && currNode->numara!=input)
	{
		prevNode = currNode;
		currNode = currNode->sonraki;
		currIndex++;
	}
	if(currNode)
	{
		if(prevNode)
		{
			prevNode->sonraki=currNode->sonraki;
			delete currNode;
		}
		else
		{
			head=currNode->sonraki;
			delete currNode;
		}
		return currIndex;
	}
	return 0;
}

//displayList Komutu Öðrencileri teker teker ekrana yazdýrýr
void List::displayList()
{
	int num=0;
	//Burada currNode'u heade eþitlememizin sebebi düðüme baþtan baþlamak
	node* currNode=head;
	//currNode NULL yani sona gelene kadar bu iþlemleri yapar.
	while(currNode!=NULL)
	{
		cout<<""<<currNode->numara<<" "<<currNode->ad<<" "<<currNode->soyad<<" "<<currNode->bolum<<endl;
		currNode=currNode->sonraki;
		num++;
	}
	cout<<"Listedeki Ogrenci Sayilari: "<<num<<endl;
}

//Kullanýcýdan numara, ad, soyad, bolum ve ders girdisi alir ve ayrý bir baðlantýlý listeye ekler.
node* List2::dersEkle(int index,double numara,char* ad,char* soyad,char* bolum,char* alinanDers)
{
	if(index<0)
		return NULL;
	int currIndex=1;
	node* currNode=head;
	while(currNode&&index>currIndex)
	{
		currNode = currNode->sonraki;
		currIndex++;
	}
	if(index >0&&currNode==0)
	return 0;
	node* newNode = new node;
	newNode->numara=numara;
	newNode->ad=ad;
	newNode->soyad=soyad;
	newNode->bolum=bolum;
	newNode->alinanDers=alinanDers;
	
	if(index==0)
	{
		newNode->sonraki=head;
		last=head=newNode;
		newNode->onceki=NULL;
	}
	else
	{
		newNode->sonraki=currNode->sonraki;
		currNode->sonraki=newNode;
		newNode->onceki=currNode;
		last=newNode;
	}
	return newNode;
}

int List2::dersSil(double input)
{
	node* prevNode=NULL;
	node* currNode=head;
	int currIndex=1;
	while(currNode && currNode->numara!=input)
	{
		prevNode = currNode;
		currNode = currNode->sonraki;
		currIndex++;
	}
	if(currNode)
	{
		if(prevNode)
		{
			prevNode->sonraki=currNode->sonraki;
			delete currNode;
		}
		else
		{
			head=currNode->sonraki;
			delete currNode;
		}
		return currIndex;
	}
	return 0;
}

int List2::dersArama(double input)
{
	node* currNode=head;
	int currIndex=1;
	while(currNode && currNode->numara!=input)
	{
		currNode=currNode->sonraki;
		currIndex++;
	}
	if(currNode)
	cout<<currNode->ad<<" "<<currNode->soyad<<" "<<currNode->bolum<<" "<<currNode->alinanDers<<endl;
	return 0;
}

void List2::sadeceProgramlamaDersi()
{
	int sayac=0;
	node* currNode=head;
	while(currNode!=NULL)
	{
		if(currNode->alinanDers=="BilgisayarProgramlama")
		{
			cout<<""<<currNode->numara<<" "<<currNode->ad<<" "<<currNode->soyad<<" "<<currNode->bolum<<" "<<endl;
			sayac++;
		}
		currNode=currNode->sonraki;
	}
	cout<<"Bilgisayar Programlama Dersini Alan Toplam Ogrenci Sayisi: "<<sayac<<endl;	
}

void List2::programlamaDersiAGrubu()
{
	char *soyadi=new char[20];
	int sayac=0;
	node* currNode=head;
	while(currNode!=NULL)
	{
		soyadi=currNode->soyad;
		if(currNode->alinanDers=="BilgisayarProgramlama")
			if(soyadi[0]>='A'&&soyadi[0]<='K')
				{
					cout<<""<<currNode->numara<<" "<<currNode->ad<<" "<<currNode->soyad<<" "<<currNode->bolum<<" "<<endl;
					sayac++;
				}
		currNode=currNode->sonraki;
	}
	cout<<"Bilgisayar Programlama Dersini Alan Ogrencilerin Soyisimlerinin A-K Arasi Olanlarin Sayisi: "<<sayac<<endl;
}
void List2::programlamaDersiBGrubu()
{
	char *soyadi=new char[20];
	int sayac=0;
	node* currNode=head;
	while(currNode!=NULL)
	{
		soyadi=currNode->soyad;
		if(currNode->alinanDers=="BilgisayarProgramlama")
			if(soyadi[0]>='L'&&soyadi[0]<='Z')
			{
				cout<<""<<currNode->numara<<" "<<currNode->ad<<" "<<currNode->soyad<<" "<<currNode->bolum<<" "<<endl;
				sayac++;
			}
			currNode=currNode->sonraki;
	}
	cout<<"Bilgisayar Programlama Dersini Alan Ogrencilerin Soyisimlerinin L-Z Arasi Olanlarin Sayisi: "<<sayac<<endl;
}

void List2::displayList2()
{
	int sayac=0;
	node* currNode=head;
	while(currNode!=NULL)
	{
		cout<<""<<currNode->numara<<" "<<currNode->ad<<" "<<currNode->soyad<<" "<<currNode->bolum<<" "<<currNode->alinanDers<<endl;
		currNode=currNode->sonraki;
		sayac++;
	}
	cout<<"Ders Alan Ogrenci Sayilari: "<<sayac<<endl;
}

//bu fonksiyon kümeleme sýralama algortitmasýnýn alt iþlemi olan heapify tarafýný ustleniyor.
void List2::heapify(int dizi[],int n,int i)
{
	int enBuyuk=i;//baþlangýçta kökü en buyuk olarak eþitliyoruz.
	int sol=2*i+1;//kökün sol tarafý
	int sag=2*i+2;//kökün sað tarafý
	
	//eðer kökün sol tarafý kökten büyükse bu iþlemler uygulanmalý
	if(sol<n && dizi[sol]>dizi[enBuyuk])
	enBuyuk=sol;
	
	//eðer kökün sað tarafý kökten daha büyükse bu iþlemler uygulanmalý
	if(sag<n && dizi[sag]>dizi[enBuyuk])
	enBuyuk=sag;
	
	//eger dizinin en buyuk elemaný kök deðilse takas iþlemi uygulanmalý
	if(enBuyuk!=i)
	{
		swap(dizi[i],dizi[enBuyuk]);
		
		heapify(dizi,n,enBuyuk);
	}
}

//main fonksiyonu tarafýndan çaðýrýlacak olan kümeleme sýralama algoritmasý
void List2::kumelemeSiralama(int dizi[],int n)
{
	//burada yapmamýz gereken düðümü baþtan sona kontrol edip o düðümde BilgisayarProgramlama dersini alan bir öðrenci varsa
	//o öðrencinin numarasýný diziye ekleyip, eklediðimiz diziden sýralama yapmaktýr.
	node *currNode=head;
	n=0;
	while(currNode!=NULL)
	{
		if(currNode->alinanDers=="BilgisayarProgramlama")
		{
		dizi[n]=currNode->numara;
		n++;
		}
		currNode=currNode->sonraki;				
	}
	
	//diziyi yeniden düzenleme
	for(int i=n/2-1;i>=0;i--)
		heapify(dizi,n,i);
	
	//heap den bire bir eleman çekme
	for(int i=n-1;i>=0;i--)
	{
		swap(dizi[0],dizi[i]);
		
		heapify(dizi,i,0);
	}
	
	cout<<"Kumeleme Siralama Algoritmasi\n"<<endl;
	for(int i=0;i<n;++i)
		cout<<dizi[i]<<" "<<endl;
	cout<<"\n";
}

List::~List(void)
{
	node* currNode=head;
	node* nextNode=NULL;
	
	while(currNode!=NULL)
	{
		nextNode=currNode->sonraki;
		//destroy the current Node
		delete currNode;
		currNode=nextNode;
	}
}
List2::~List2(void)
{
	node* currNode=head;
	node* nextNode=NULL;
	
	while(currNode!=NULL)
	{
		nextNode=currNode->sonraki;
		delete currNode;
		currNode=nextNode;
	}
}

//Baðlanýtýlý Liste Iþlemleri Sonu



//B+ Islemleri

class NonLeafNode : public node {
	/*
  		Hedef: B+ tree'nin yapraksýz düðümü için bir sýnýf tanýmlar
		Yaklaþým: Node sýnýfý düðüm yapýsýný tanýmlar
	*/
public:
  vector<node *> Children;
  NonLeafNode() {
    isLeaf = false;
    Parent = NULL;
  }
};

class LeafNode : public node {
  	/*
		Hedef: B+ tree'nin yapraklý düðümü için bir sýnýf tanýmlanýr
		Yaklaþým: Bir yaprak düðümü (Genel düðümden inherit eder)
	*/
public:
  node *Next;
  vector<string> Value;
  LeafNode() {
    isLeaf = true;
    Next = NULL;
    Parent = NULL;
  }
};

class BPTree {
  /*
		Hedef: B+ tree sýnýfý oluþturma
		Yaklaþým: sýnýf tanýmlama
	*/
private:
  node *head;
  int n;      // aðacýn derecesi

public:
  BPTree(int);
  void insert(double, string);
  void remove(double);
  string find(double);
  void printKeys();
  void printValues();
  ~BPTree();
};


BPTree::BPTree(int degree) {
  // Hedef: B+ tree sýnýfýnýn yapýcý fonksiyonu, aðacý oluþturmayý hedefler.

  n = degree;
  head = new LeafNode();
}

BPTree::~BPTree() {
  // Hedef: B+ aðacýnýn yýkýcý fonksiyonu aðacý silmeyi hedefler.
	// Yapýlacaklar: Doðru olmayan, bütün aðacý silmem lazým, sadece kök düðümü deðil
	
  if (head) {
    delete head;
  }
}

void BPTree::insert(double key, string value) {
  	// Hedef: B+ aðacýna eleman eklemeyi hedefler
	// Eleman için uygun yeri bul

 	 node *t = this->head; // kökten baþlama
	

  	while (!t->isLeaf) {  // bir yaprak düðümüne ulaþana kadar
    int flag = 0;
    // anahtar (key) dizisinde daha büyük bir deðer bulunana kadar, ileriye devam et
    for (int i = 0; i < t->Keys.size(); ++i) {
     // daha büyük deðerde eleman bulundu
      if (t->Keys[i] > key) {
        // Yapraksýz düðüm olarak þeklini deðiþtir ve i. çocuða git
        t = ((NonLeafNode *)t)->Children[i];
        flag = 1;
        break;
      }
    }
    // eðer hiçbir anahtar daha büyük deðilse, en büyük anahtar odur
    if (!flag) {
            // smartly put value  ?? check
      t = ((NonLeafNode *)t)->Children[t->Keys.size()];
    }
  }


  // eðer anahtar sonuncudan sonra ise (ayrýca anahtar güncel olarak 0 anahtara sahipse ele alýnýr)
  if (t->Keys.size() == 0 || key > t->Keys.back()) {
    t->Keys.push_back(key);
    ((LeafNode *)t)->Value.push_back(value);

  } else {
    for (int i = 0; i < t->Keys.size(); ++i) { // yaprak düðümüne ekleme
      if (t->Keys[i] == key) {
        cout << "Iki tane ayni olan anahtar ekleyemezsiniz!" << endl;
        return;
      } else if (t->Keys[i] > key) {
        t->Keys.insert(t->Keys.begin() + i, key);
        ((LeafNode *)t)
            ->Value.insert(((LeafNode *)t)->Value.begin() + i, value);
        break;
      }
    }
  }
  if (t->Keys.size() > this->n) { // yaprak düðümünü ayýrma
    node *tnew = new LeafNode();
    tnew->Parent = t->Parent;
    
    // // ikinci yarýyla yeni yaprak yapma - anahtarlarý ekleme
    tnew->Keys.insert(tnew->Keys.begin(), t->Keys.begin() + ceil((n + 1) / 2), t->Keys.end());
    // // ikinci yarýyla yeni yaprak yapma - deðerleri ekleme
    ((LeafNode *)tnew)
        ->Value.insert(((LeafNode *)tnew)->Value.begin(),
                       ((LeafNode *)t)->Value.begin() + ceil((n + 1) / 2),
                       ((LeafNode *)t)->Value.end());
    
    // ikinci yarým anahtarlarý ve deðerleri orjinalden silme
    t->Keys.erase(t->Keys.begin() + ceil((n + 1) / 2), t->Keys.end());
    ((LeafNode *)t)
        ->Value.erase(((LeafNode *)t)->Value.begin() + ceil((n + 1) / 2),
                      ((LeafNode *)t)->Value.end());
    
    // yeni yapýlmýþ yaprak noktalarýna NULL deðeri veriliyor
    ((LeafNode *)tnew)->Next = ((LeafNode *)t)->Next;
    // eski yaprak noktalarýný yeni yaprak düðümüne
    ((LeafNode *)t)->Next = tnew;


    key = t->Keys[ceil((n + 1) / 2) - 1];

    // t'nin ebeveyni yapraksýz düðümdür
    while (t->Parent != NULL) {
      //þimdi yeni olan t=t->parent dýr, çünkü bütün sürecin ebeveyn üzerinde tamamlanmasý gerekir.
      t = t->Parent;

      for (int i = 0; i < t->Keys.size(); ++i) {

        // eðer güncel anahtar varolan anahtarlar içerisinde en büyüðüyse
        if (key > t->Keys.back()) {
          // because it is largest, push it at last çünkü o en büyüðü, onu en sona at
          t->Keys.push_back(key);
          // yeni ayrýlmýþ yaprak düðümünü ebeveyninin çocuk dizisine at
          ((NonLeafNode *)t)->Children.push_back(tnew);
          break;
        }
        // eðer güncel anahtar en büyüðü deðilse
        else if (t->Keys[i] > key) {
          // t çocuðunu onun çocuk dizisine ekle
          t->Keys.insert(t->Keys.begin() + i, key);
          // tnew çocuðunu onun çocuðunun dizisine ekleme
          ((NonLeafNode *)t) ->Children.insert(((NonLeafNode *)t)->Children.begin() + i + 1, tnew);
          break;
        }
      }
      // eðer ebeveynlerin ayrýca ayrýlmaya ihtiyacý varsa
      if (t->Keys.size() > this->n) {
        // yeni düðüm yap
        node *nright = new NonLeafNode();
        nright->Parent = t->Parent;
        // ikiye ayýr
        nright->Keys.insert(nright->Keys.begin(),
                            t->Keys.begin() + floor((n + 2) / 2),
                            t->Keys.end());
        ((NonLeafNode *)nright)
            ->Children.insert(((NonLeafNode *)nright)->Children.begin(),
                              ((NonLeafNode *)t)->Children.begin() +
                                  floor((n + 2) / 2),
                              ((NonLeafNode *)t)->Children.end());
        for (int i = floor((n + 2) / 2);
             i < ((NonLeafNode *)t)->Children.size(); ++i) {
          ((NonLeafNode *)t)->Children[i]->Parent = nright;
        }
        key = t->Keys[floor((n + 2) / 2) - 1];
        t->Keys.erase(t->Keys.begin() + floor((n + 2) / 2) - 1, t->Keys.end());
        ((NonLeafNode *)t)
            ->Children.erase(((NonLeafNode *)t)->Children.begin() +
                                 floor((n + 2) / 2),
                             ((NonLeafNode *)t)->Children.end());
        tnew = nright;
      } else {
        tnew->Parent = t;
        return;
      }
    }
    // köke eriþtiðimizde
    if (t->Parent == NULL) {
      // yapraksýz düðüm oluþtur
      t->Parent = new NonLeafNode();
      
      // t ve tnew'i bu yeni yapraksýz düðümün çocuk dizisine ekle
      ((NonLeafNode *)t->Parent) -> Children.insert(((NonLeafNode *)t->Parent)->Children.begin(), t);
      ((NonLeafNode *)t->Parent) -> Children.insert(((NonLeafNode *)t->Parent)->Children.begin() + 1, tnew);
      
      if (t->isLeaf) {
        // yaprak düðümünün son anahtarýný ebeveyn düðümünün baþýna taþý
        (t->Parent)->Keys.insert((t->Parent)->Keys.begin(), t->Keys.back());
      } else {
        // t son çocuðunun son anahtarýný t'nin ebeveyninin baþlangýcýna taþý
        (t->Parent)->Keys.insert(
            (t->Parent)->Keys.begin(),
            ((NonLeafNode *)t)->Children.back()->Keys.back());
      }
      tnew->Parent = t->Parent;
      head = t->Parent;
    }

  } else {
    return;
  }
}

// ekleme iþlemi sonu

string BPTree::find(double key) {
	// Hedef: fonksiyon, B+ aðacýnýn içerisinde elemanlarý aramayý hedefler

  node *t = this->head;
  while (!t->isLeaf) { // doðru yeri bul
    int flag = 0;
    for (int i = 0; i < t->Keys.size(); ++i) {
      if (t->Keys[i] >= key) {
        t = ((NonLeafNode *)t)->Children[i];
        flag = 1;
        break;
      }
    }
    if (!flag) {
      t = ((NonLeafNode *)t)->Children[t->Keys.size()];
    }
  }
  for (int i = 0; i < t->Keys.size(); ++i) {
    if (t->Keys[i] == key) {
      return ((LeafNode *)t)->Value[i];
    }
  }
  return "Bu anahtar B+ agacinin icerisinde yer almiyor!";
}

void BPTree::printKeys() {
  	//	Hedef: fonksiyon, B+ aðacýnýn içerisindeki bütün anahtarlarý yazdýrmayý hedefler

  if (head->Keys.size() == 0) {
    cout << "[]" << endl;
    return;
  }
  vector<node *> q;
  q.push_back(head);
  while (q.size()) {
    unsigned long size = q.size();
    for (int i = 0; i < size; ++i) {
      if (!q[i]->isLeaf) {
        for (int j = 0; j < ((NonLeafNode *)q[i])->Children.size(); ++j) {
          q.push_back(((NonLeafNode *)q[i])->Children[j]);
        }
      }
      cout << "[";
      int nk = 0;
      for (nk = 0; nk < q[i]->Keys.size() - 1; ++nk) {
        cout << q[i]->Keys[nk] << ",";
      }
      cout << q[i]->Keys[nk] << "] ";
    }
    q.erase(q.begin(), q.begin() + size);
    cout << endl;
  }
}

void BPTree::printValues() {
  // Hedef: fonksiyon, B+ içerisindeki bütün string deðerleri yazdýrmayý hedefler
  

  node *t = this->head;
  while (!t->isLeaf) {
    t = ((NonLeafNode *)t)->Children[0];
  }
  while (t != NULL) {
    for (int i = 0; i < t->Keys.size(); ++i) {
      cout << ((LeafNode *)t)->Value[i] << endl;
    }
    t = ((LeafNode *)t)->Next;
  }
}

void BPTree::remove(double key) {
  node *t = this->head;

  // Girilen anahtarýn düðümünü bul
  while (!t->isLeaf) { // Yerini bul
    int flag = 0;
    for (int i = 0; i < t->Keys.size(); ++i) {
      if (t->Keys[i] >= key) {
        t = ((NonLeafNode *)t)->Children[i];
        flag = 1;
        break;
      }
    }
    if (!flag) {
      t = ((NonLeafNode *)t)->Children[t->Keys.size()];
    }
  }

  // anahtarý ve deðerini sil
  int flag = 0;
  for (int i = 0; i < t->Keys.size(); ++i) {
    if (t->Keys[i] == key) {
      t->Keys.erase(t->Keys.begin() + i);
      ((LeafNode *)t)->Value.erase(((LeafNode *)t)->Value.begin() + i);
      flag = 1;
      break;
    }
  }
  // bulunamazsa
  if (!flag) {
    cout << "Silmek istediðiniz anahtar yoktur!" << endl;
    return;
  }
	// ayarlama sadece gerekenden daha az düðüm olduðunda gerekir
  if (((LeafNode *)t)->Value.size() < ceil((n + 1) / 2) && t->Parent != NULL) {

    node *Rsibling;
    node *Lsibling;
    Rsibling = Lsibling = NULL;

    // iç düðüm
    int Child_num = -1;

    // anahtar dizisinin içerisinde, anahtarýn pozisyonunu bul
    for (int i = 0; i < ((NonLeafNode *)t->Parent)->Children.size(); ++i) {
      if (((NonLeafNode *)t->Parent)->Children[i] == t) {
        Child_num = i;
        break;
      }
    }

    // bulunanýn solu SOL KARDEÞ
    if (Child_num - 1 >= 0) {
      Lsibling = ((NonLeafNode *)t->Parent)->Children[Child_num - 1];
    }
    // bulunanýn saðý SAÐ KARDEÞ
    if (Child_num + 1 < ((NonLeafNode *)t->Parent)->Children.size()) {
      Rsibling = ((NonLeafNode *)t->Parent)->Children[Child_num + 1];
    }

    // kardeþler þimdi biliniyor

    // eðer sað kardeþ yeterli düðüme sahipse, buradan (saðdan) deðer götür
    if (Rsibling != NULL && ((LeafNode *)Rsibling)->Value.size() - 1 >= ceil((n + 1) / 2)) {

      // sað kardeþin ilk anahtarýný al ve bu anahtarý þu anki düðüme ekle
      t->Keys.push_back(Rsibling->Keys.front());
      ((LeafNode *)t)->Value.push_back(((LeafNode *)Rsibling)->Value.front());
      
      // bu anahtarý sað çocuktan sil
      Rsibling->Keys.erase(Rsibling->Keys.begin());
      ((LeafNode *)Rsibling)->Value.erase(((LeafNode *)Rsibling)->Value.begin());

      // bu deðiþikliklerin ayrýca güncel düðümün ebeveynine yansýtýlmasý gerekir
      t->Parent->Keys[Child_num] = t->Keys.back();
      return;
    }

    // eðer sað kardeþ yeterli düðüme sahipse, buradan(soldan) götür
    else if (Lsibling != NULL && ((LeafNode *)Lsibling)->Value.size() - 1 >= ceil((n + 1) / 2)) {
      
      // sol kardeþin son anahtarýný al ve þu anki düðüme ekle
      t->Keys.insert(t->Keys.begin(), Lsibling->Keys.back());
      ((LeafNode *)t)->Value.insert(((LeafNode *)t)->Value.begin(),
                         ((LeafNode *)Lsibling)->Value.back());

      // bu anahtarý sol çocuktan sil
      Lsibling->Keys.erase(Lsibling->Keys.end() - 1);
      ((LeafNode *)Lsibling) ->Value.erase(((LeafNode *)Lsibling)->Value.end() - 1);

      // bu deðiþiklikler ayrýca þu anki düðümün ebeveynine yansýtýlmasý gerekir.
      t->Parent->Keys[Child_num - 1] = Lsibling->Keys.back();
      return;
    }

    // kardeþler yardým edemezse, güçlendirmek için ayrýlmasý gerekir
    else {
      // sað çocuk gerekenden daha azsa
      if (Rsibling != NULL && ((LeafNode *)Rsibling)->Value.size() - 1 < ceil((n + 1) / 2)) {

        // sað kardeþin tüm anahtarlarýný þu anki düðüme böl
        t->Keys.insert(t->Keys.end(), Rsibling->Keys.begin(), Rsibling->Keys.end());
        // ve ayrýca deðerleri
        ((LeafNode *)t) ->Value.insert(((LeafNode *)t)->Value.end(),
                           ((LeafNode *)Rsibling)->Value.begin(),
                           ((LeafNode *)Rsibling)->Value.end());
        
        // þimdi sað kardeþin silinmesi gerekli

        // current->next = right sibling -> next yap
        ((LeafNode *)t)->Next = ((LeafNode *)Rsibling)->Next;

		// þimdi güvenilir bir þekilde sað kardeþi silebiliriz
		
		
        // ilk olarak deðiþiklikleri onun ilk ebeveynine yansýt
        
        t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num);
        // bütün sað kardeþ düðümünü sil
        ((NonLeafNode *)t->Parent)->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() + Child_num + 1);

        // þu anki pointer yerinde (sað kardeþin solunda) ve sað kardeþ silindi
      } 
      // sað kardeþ istenilenden az
      else if (Lsibling != NULL && ((LeafNode *)Lsibling)->Value.size() - 1 < ceil((n + 1) / 2)) {

        // sol kardeþin bütün anahtarlarýný þu anki düðüme böl
        Lsibling->Keys.insert(Lsibling->Keys.end(), t->Keys.begin(), t->Keys.end());

        // ayrýca deðerlerini de 
        ((LeafNode *)Lsibling) ->Value.insert(((LeafNode *)Lsibling)->Value.begin(),
                           ((LeafNode *)t)->Value.begin(),
                           ((LeafNode *)t)->Value.end());

        
        // þimdi sol kardeþin silinmesi gerekli
        
        // left sibling -> next = current->next yap
        
        ((LeafNode *)Lsibling)->Next = ((LeafNode *)t)->Next;

        // þimdi sol kardei güvenilir bir þekilde silebiliriz
        
        // ilk olarak deðiþiklikler onun ebeveynine yansýtýlýr
        t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num - 1);

        // bütün sol kardeþ düðümünü sil
        ((NonLeafNode *)t->Parent) ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() + Child_num);

        // þu anki pointer orijinal sola deðiþtirildi ve þu anki silindi
        t = Lsibling;
      }

      // þu anki düðüm süreci baþa eriþmiyorsa, tekrarlý bir þekilde bütün düðümlerin arasýnda iþlemden geçir
      while (t->Parent != this->head) {

        Rsibling = Lsibling = NULL;
        // iþlemi baþlatmak için t yi t->parent e taþý
        t = t->Parent;

        // eðer yeterli çocuða sahipse, iþlenecek bir þey yok
        if (((NonLeafNode *)t)->Children.size() >= floor((n + 2) / 2)) {
          return;
        }

        //þu anki düðümü bul ve düðümün pozisyonunu child_num'da tut
        int Child_num = -1;
        for (int i = 0; i < ((NonLeafNode *)t->Parent)->Children.size(); ++i) {
          if (((NonLeafNode *)t->Parent)->Children[i] == t) {
            Child_num = i;
            break;
          }
        }

        // þu ankinin solu
        if (Child_num - 1 >= 0) {
          Lsibling = ((NonLeafNode *)t->Parent)->Children[Child_num - 1];
        }

        // þu ankinin saðý
        if (Child_num + 1 < ((NonLeafNode *)t->Parent)->Children.size()) {
          Rsibling = ((NonLeafNode *)t->Parent)->Children[Child_num + 1];
        }

        // eðer sað kardeþ yeterli düðümlere sahipse, buradan al
        if (Rsibling != NULL && ((NonLeafNode *)Rsibling)->Children.size() - 1 >= floor((n + 2) / 2)) {
          
          // sað kardeþten ilk çocuðu al ve yukarýdakine benzer olarak iþlemleri yap
          ((NonLeafNode *)t) ->Children.push_back(((NonLeafNode *)Rsibling)->Children.front());
          t->Keys.push_back(t->Parent->Keys[Child_num]);
          t->Parent->Keys[Child_num] = Rsibling->Keys.front();
          ((NonLeafNode *)Rsibling) ->Children.erase(((NonLeafNode *)Rsibling)->Children.begin());
          Rsibling->Keys.erase(Rsibling->Keys.begin());
          ((NonLeafNode *)t)->Children.back()->Parent = t;
          return;
        } 

        // eðer sol kardeþ yeterli düðümlere sahipse
        else if (Lsibling != NULL && ((NonLeafNode *)Lsibling)->Children.size() - 1 >= floor((n + 2) / 2)) {

          // sol kardeþin son çocuðunu al ve yukarýdakine benzer olarak iþlemleri yap
          ((NonLeafNode *)t) ->Children.insert(((NonLeafNode *)t)->Children.begin(), ((NonLeafNode *)Lsibling)->Children.back());
          t->Keys.insert(t->Keys.begin(), t->Parent->Keys[Child_num - 1]);
          t->Parent->Keys[Child_num] = Lsibling->Keys.back();
          ((NonLeafNode *)Lsibling) ->Children.erase(((NonLeafNode *)Lsibling)->Children.end() - 1);
          Lsibling->Keys.erase(Lsibling->Keys.end() - 1);
          ((NonLeafNode *)t)->Children.front()->Parent = t;
          return;
        } 

        // eðer sað tarafýnda yeterli deðilse, bölünecek
        else if (Rsibling != NULL && ((NonLeafNode *)Rsibling)->Children.size() - 1 < floor((n + 2) / 2)) {
          ((NonLeafNode *)Rsibling) ->Children.insert(((NonLeafNode *)Rsibling)->Children.begin(),
                                ((NonLeafNode *)t)->Children.begin(),
                                ((NonLeafNode *)t)->Children.end());
          Rsibling->Keys.insert(Rsibling->Keys.begin(),
                                t->Parent->Keys[Child_num]);
          Rsibling->Keys.insert(Rsibling->Keys.begin(), t->Keys.begin(),
                                t->Keys.end());
          for (int i = 0; i < ((NonLeafNode *)t)->Children.size(); ++i) {
            ((NonLeafNode *)t)->Children[i]->Parent = Rsibling;
          }
          t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num);
          ((NonLeafNode *)t->Parent)
              ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() +
                               Child_num);
          t = Rsibling;
        }
		 
        // eðer sol tarafýnda yeterli deðilse, bölünecek
        
        else if (Lsibling != NULL &&
                   ((NonLeafNode *)Lsibling)->Children.size() - 1 <
                       floor((n + 2) / 2)) {
          ((NonLeafNode *)Lsibling)
              ->Children.insert(((NonLeafNode *)Lsibling)->Children.end(),
                                ((NonLeafNode *)t)->Children.begin(),
                                ((NonLeafNode *)t)->Children.end());
          Lsibling->Keys.insert(Lsibling->Keys.end(),
                                t->Parent->Keys[Child_num - 1]);
          Lsibling->Keys.insert(Lsibling->Keys.end(), t->Keys.begin(),
                                t->Keys.end());
          for (int i = 0; i < ((NonLeafNode *)t)->Children.size(); ++i) {
            ((NonLeafNode *)t)->Children[i]->Parent = Lsibling;
          }
          t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num - 1);
          ((NonLeafNode *)t->Parent)
              ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() +
                               Child_num);
          t = Lsibling;
        }
      }

      // baþa eriþildi ve baþýn anahtarý yok
      if (t->Parent == this->head && this->head->Keys.size() == 0) {
        // þu anki düðüm baþ oldu
        this->head = t;
        return;
      }
    }
  }
}

int main(void)
{
	BPTree t(3);
	List list;
	List2 list2;
	list.insertNode(0,1857,"Abdullah","Esen","BilgisayarMuhendisligi");
	list.insertNode(1,1977,"Deniz","Zeybek","BiyomedikalMuhendisligi");
	list.insertNode(2,8574,"Esra","Ayhan","BilgisayarMuhendisligi");
	list.insertNode(3,1050,"Ilayda","Kahraman","BilgisayarMuhendisligi");
	list.insertNode(4,2530,"Salih","Akin","BiyomedikalMuhendisligi");
	list.insertNode(5,6742,"Burak","Karatoprak","BilgisayarMuhendisligi");
	list.insertNode(6,5782,"Yeliz","Mutlu","BiyomedikalMuhendisligi");
	list.insertNode(7,7213,"Kerem","Pullu","BilgisayarMuhendisligi");
	list.insertNode(8,8430,"Feyza","Kuleli","BilgisayarMuhendisligi");
	list.insertNode(9,9474,"Rana","Gedik","BilgisayarMuhendisligi");
	list.insertNode(10,3567,"Feraye","Can","BiyomedikalMuhendisligi");
	list.insertNode(11,4678,"Faruk","Bilgili","BilgisayarMuhendisligi");
	list.insertNode(12,2563,"Selin","Demir","BilgisayarMuhendisligi");
	list.insertNode(13,1560,"Merve","Gunduz","BiyomedikalMuhendisligi");
	list.insertNode(14,5981,"Kadir","Bayri","BilgisayarMuhendisligi");
	list2.dersEkle(0,1857,"Abdullah","Esen","BilgisayarMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(1,1977,"Deniz","Zeybek","BiyomedikalMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(2,8574,"Esra","Ayhan","BilgisayarMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(3,1050,"Ilayda","Kahraman","BilgisayarMuhendisligi","VeritabaniYonetimSistemleri");
	list2.dersEkle(4,2530,"Salih","Akin","BiyomedikalMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(5,6742,"Burak","Karatoprak","BilgisayarMuhendisligi","VeritabaniYonetimSistemleri");
	list2.dersEkle(6,5782,"Yeliz","Mutlu","BiyomedikalMuhendisligi","VeritabaniYonetimSistemleri");
	list2.dersEkle(7,7213,"Kerem","Pullu","BilgisayarMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(8,8430,"Feyza","Kuleli","BilgisayarMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(9,9474,"Rana","Gedik","BilgisayarMuhendisligi","VeritabaniYonetimSistemleri");
	list2.dersEkle(10,3567,"Feraye","Can","BiyomedikalMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(11,4678,"Faruk","Bilgili","BilgisayarMuhendisligi","VeritabaniYonetimSistemleri");
	list2.dersEkle(12,2563,"Selin","Demir","BilgisayarMuhendisligi","VeritabaniYonetimSistemleri");
	list2.dersEkle(13,1560,"Merve","Gunduz","BiyomedikalMuhendisligi","BilgisayarProgramlama");
	list2.dersEkle(14,5981,"Kadir","Bayri","BilgisayarMuhendisligi","BilgisayarProgramlama");
	int dizi[]={1857,1977,8574,1050,2530,6742,5782,7213,8430,9474,3567,4678,2563,1560,5981};
	string dizgi[]={"Abdullah","Deniz","Esra","Ilayda","Salih","Burak","Yeliz","Kerem","Feyza","Rana","Feraye","Faruk","Selin","Merve","Kadir"};
	int index1=0;
	while(dizi[index1]!=dizi[15])
	{
		t.insert(dizi[index1],dizgi[index1]);
		index1++;
	}
	string satir;
	double numara,index=15;
	int sayi;
	do
	{
	cout<<"\n1-->Listeye Eleman Ekleme\n2-->Listeden Eleman Silme\n3-->Liste Uzerinden Arama Yapma\n4-->Listeyi Goruntuleme"<<endl;
	cout<<"5-->Ogrenciye Ders ekleme\n6-->Ders Alan Ogrenci Kaydini Silme\n7-->Ders Alan Ogrenciler Arasindan Arama Yapma"<<endl;
	cout<<"8-->Ders Alan Ogrencileri Goruntuleme\n9-->Sadece Programlama Dersini Alan Ogrenci Listesini Goruntuleme\n10-->Programlama Dersi A Grubunu Listeleme"<<endl;
	cout<<"11-->Programlama Dersi B Grubu Listeleme\n12-->Bilgisayar Programlama Dersini Alan Ogrencileri Kumeleme Siralama Algoritmasina Gore Listeleme"<<endl;
	cout<<"13-->B+ Agacina Ogrenci Ekleme\n14-->B+ Agacindaki Ogrenciyi Bulma\n15-->B+ Agacindaki Numaralari Yazma ve Siralama"<<endl;
	cout<<"16-->B+ Agacindaki Ogrencileri Yazma ve Siralama\n17-->B+ Agacindaki Ogrenciyi Silme\n0-->Cikis Islemi"<<endl;
	cin>>sayi;
	switch(sayi)
	{
		case 1:
		{
			cout<<"Eklemek istediginiz ogrencinin numarasini, adini, soyadini ve bolumunu giriniz. "<<endl;
			char *ad=new char[20];
			char *soyad=new char[20];
			char *bolum=new char[30];
			cin>>numara>>ad>>soyad>>bolum;
        	list.insertNode(index,numara,ad,soyad,bolum);
        	index++;
        	cout<<ad<<" isimli ogrenci dugume eklendi"<<endl;
			break;
		}
		case 2:
		{
			cout<<"Silmek istediginiz ogrencinin numarasini giriniz."<<endl;
			cin>>numara;
			list.deleteNode(numara);
			cout<<numara<<" numarali ogrencinin kaydi silindi."<<endl;
			break;
		}
		case 3:
		{
			cout<<"Aramak istediginiz ogrencinin numarasini giriniz. "<<endl;
			cin>>numara;
			cout<<"Numarasini girdiginiz ogrencinin index\'i : "<<list.findNode(numara)<<endl;
			break;
		}
		case 4:
		{
			list.displayList();
			break;
		}
		case 5:
		{
			index=15;
			char *adi=new char[20];
			char *soyadi=new char[20];
			char *bolumu=new char[20];
			char *alinanDers=new char[30];
			cout<<"Ders eklemek istediginiz ogrencinin numarasini, adini, soyadini, bolumunu ve hangi dersi eklemek istediginizi giriniz."<<endl;
			cin>>numara>>adi>>soyadi>>bolumu>>alinanDers;
			list.insertNode(index,numara,adi,soyadi,bolumu);
			list2.dersEkle(index,numara,adi,soyadi,bolumu,alinanDers);
			index++;
			cout<<"Ogrencinin bilgileri ve alacagi ders dugume eklendi"<<endl;
			break;
		}
		case 6:
		{
			cout<<"Silmek istediginiz ogrencinin numarasini giriniz."<<endl;
			cin>>numara;
			list.deleteNode(numara);
			list2.dersSil(numara);
			cout<<numara<<" numarali ogrencinin kaydi silindi"<<endl;
			break;
		}
		case 7:
		{
			cout<<"Aramak istediginiz ogrencinin numarasini giriniz."<<endl;
			cin>>numara;
			cout<<list2.dersArama(numara)<<endl;
			break;
		}
		case 8:
		{
			list2.displayList2();
			break;
		}
		case 9:
		{
			list2.sadeceProgramlamaDersi();
			break;
		}
		case 10:
		{
			list2.programlamaDersiAGrubu();
			break;
		}
		case 11:
		{
			list2.programlamaDersiBGrubu();
			break;
		}
		case 12:
		{
			int n;
			int dizimiz[10];
			list2.kumelemeSiralama(dizimiz,n);
			break;
		}
		case 13:
		{
			double k;
			string s;
			cout<<"Numarayi ve Isimi Giriniz "<<endl;
			cin>>k>>s;
	  		t.insert(k,s);
	  		cout<<"B+ agacina eleman eklendi"<<endl;
			break;
		}
		case 14:
		{
			double x;
      		cout<<"Aranacak ogrencinin numarasini giriniz: ";
      		cin>>x;
      		cout<<t.find(x)<<endl;
			break;
		}
		case 15:
		{
			t.printKeys();
			break;
		}
		case 16:
		{
			t.printValues();
			break;
		}
		case 17:
		{
			double x;
      		cout<<"Silinecek numarayi giriniz: "<<endl;
      		cin>>x;
      		t.remove(x);
      		cout<<x<<" numarali anahtar b+ agacindan silindi."<<endl;
			break;
		}
	}
}while(sayi);



return 0;
}
