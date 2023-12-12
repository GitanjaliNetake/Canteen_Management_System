#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

class MenuItem  {
public:
   string name;
double price;

    MenuItem(const string& _name, double _price) : name(_name), price(_price) {}
};

class Order {
public:
    string itemName;
    int quantity;

    Order(const string& _itemName, int _quantity) : itemName(_itemName), quantity(_quantity) {}
};

class Canteen {
private:
    vector<MenuItem> menu;
    vector<Order> orders;
     
public:

    bool isValidString(const std::string& str) {
    // Loop through each character in the string
    for (char ch : str) {
        // Check if the character is not an alphabet
        if (!isalpha(ch)) {
            return false; // Invalid character found
        }
    }

    // All characters are alphabets, so the string is valid
    return true;
}
    void addMenuItem() {

        string name;
        double price;

        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, name);
         if (isValidString(name)) {
         cout << "Enter item price: ";
        cin >> price;

        menu.emplace_back(name, price);

        cout << "Item added to the menu successfully!\n";
    } else {
        std::cout << "Please enter valid Name!!" <<endl;
    }

       
    }

    void displayMenu() {
        cout << "============Menu===========\n";
        cout << setw(10) << "Item Name" << setw(10) << "Price\n";

        for (const auto& item : menu) {
            cout << setw(10) << item.name << setw(10) << item.price << endl;
        }
    }

    void placeOrder() {
        string itemName;
        int quantity;
        int flag=0;
        cout << "Enter item name to order: ";
        cin.ignore();
        getline(cin, itemName);

       

        for (const auto& item : menu) {
            if (item.name == itemName) {
                flag=1;
                if(flag!=0){
                 cout << "Enter quantity: ";
                cin >> quantity;
                orders.emplace_back(itemName, quantity);
                cout << "Order placed successfully.\n";
                saveOrders();  // Save orders immediately after placing an order
                }

               

            }
        }
        if(flag==0){
         cout << "Item not found in the menu.\n";
         cout<<"Please Check Menu!\n";
        }

        return;
    }

    void displayOrders() {
        int flag=0;
        

        for (const auto& order : orders) {
            flag=1;
        }
        if(flag==1){
            cout << "===========Orders============\n";
        cout << setw(10) << "Item Name" << setw(10) << "     Quantity\n";
        for (const auto& order : orders) {
            cout << setw(10) << order.itemName << setw(10) << order.quantity << endl;
        }
        }else{
            cout<<"You ordered Nothig!!\n";
        }
        
    }

    double calculateTotalSales() {
        double totalSales = 0;

        for (const auto& order : orders) {
            for (const auto& item : menu) {
                if (item.name == order.itemName) {
                    totalSales += order.quantity * item.price;
                }
            }
        }

        return totalSales;
    }

    void saveMenu() {
        ofstream file("menu.txt");

        for (const auto& item : menu) {
            file << item.name << ' ' << item.price << '\n';
        }

        file.close();
    }

    void saveOrders() {
        ofstream file("orders.txt");

        for (const auto& order : orders) {
            file << order.itemName << ' ' << order.quantity << '\n';
        }

        file.close();
    }

    void loadMenu() {
        ifstream file("menu.txt");

        if (!file.is_open()) {
            cout << "No previous menu data found.\n";
            return;
        }

        menu.clear();

        string name;
        double price;

        while (file >> name >> price) {
            menu.emplace_back(name, price);
        }

        file.close();
    }

    void loadOrders() {
        ifstream file("orders.txt");

        if (!file.is_open()) {
            cout << "No previous order data found.\n";
            return;
        }

        orders.clear();

        string itemName;
        int quantity;

        while (file >> itemName >> quantity) {
            orders.emplace_back(itemName, quantity);
        }

        file.close();
    }
};

int main() {
    Canteen canteen;
    int userTypeChoice;
     string unm;
      string pass;
      int count=0;
m:
    cout << "Are you a Customer or an Owner? \n 1.Customer \n 2.Owner \n";
    cin >> userTypeChoice;

    switch(userTypeChoice) {
        case 1:  // Customer
            canteen.loadMenu();
            canteen.loadOrders();

            int customerChoice;
            do {
                cout << "1. Display Menu\n2. Place Order\n3. Display Orders\n4. Bill\n5. Exit\n";
                cout << "Enter your choice: ";
                cin >> customerChoice;

                switch (customerChoice) {
                    case 1:
                        canteen.displayMenu();
                        break;
                    case 2:
                        canteen.placeOrder();
                        break;
                    case 3:
                        canteen.displayOrders();
                        break;
                    case 4:
                        cout << "Total Bill: Rs " << fixed << setprecision(2) << canteen.calculateTotalSales() << endl;
                        break;
                    case 5:
                    goto m;
                        cout << "Exiting program.\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            } while (customerChoice != 5);

            break;

        case 2:  // Owner
           

            do{
                if(count!=0){
                    cout<<"Invalid Username and Password\n";
                }
            cout<<"\n=============   LOGIN   =============";
            cout<<"\nUsername :";
            cin>>unm;
            cout<<"Password : ";
            cin>>pass;
            count++;
            }while(!(unm=="abc@123"&&pass=="12345"));
           
            int ownerChoice;
             canteen.loadMenu();
            canteen.loadOrders();
           // if(){

           
            do {
                cout << "1. Add Item to Menu\n2. Display Menu\n3. Display Orders\n4. Exit\n";
                cout << "Enter your choice: ";
                cin >> ownerChoice;

                switch (ownerChoice) {
                    case 1:
                        canteen.addMenuItem();
                        break;
                    case 2:
                        canteen.displayMenu();
                        canteen.saveMenu();
                        break;
                   
                    case 3:
                        canteen.displayOrders();
                        canteen.saveOrders();
                       
                        break;
                    
                    case 4:
                    goto m;
                        cout << "Exiting program.\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            } while (ownerChoice != 6);
            
          /*  }else{
                cout<<"Invalid UserName and Password !";
            }*/
            break;

        default:
            cout << "Invalid user type. Exiting program.\n";
            break;
    }

    return 0;
}
