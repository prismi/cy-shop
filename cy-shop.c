#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include<limits.h>

#define MAX_PRODUCTS 200
#define MAX_CUSTOMERS 200


                                                    
typedef struct {
    char name[50];
    int reference;
    int quantity;
    float price;
    char color[20];
    char size[20];
} Product;

typedef struct {
    char firstName[50];
    char lastName[50];
    char username[50];
    char gender[10];
    char password[50];
    int purchaseHistory[3];
} Customer;

typedef struct {
 char firstName[50];
    char lastName[50];
  char username[100];
  char password[100];
char gender[10];
int purchaseHistory[3];
} customer;

  Product products[MAX_PRODUCTS];
int productCount = 0;

customer customers[MAX_CUSTOMERS];
int customerCount = 0;

void loadCustomersFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        customer newCustomer;
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d", newCustomer.firstName, newCustomer.lastName, newCustomer.username, newCustomer.gender, newCustomer.password, &newCustomer.purchaseHistory[0], &newCustomer.purchaseHistory[1], &newCustomer.purchaseHistory[2]);
        customers[customerCount++] = newCustomer;
    }

    fclose(file);
}

void saveCustomersToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
        return;
    }

    for (int i = 0; i < customerCount; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%d,%d,%d\n", customers[i].firstName, customers[i].lastName, customers[i].username, customers[i].gender, customers[i].password, customers[i].purchaseHistory[0], customers[i].purchaseHistory[1], customers[i].purchaseHistory[2]);
    }

    fclose(file);
}

bool valider_prenom(const char* prenom) {
    int length = strlen(prenom);
    
    // Vérifier si la chaîne est vide
    if (length == 0) {
        return false;
    }
    
    // Vérifier si le premier caractère est une lettre majuscule
    if (!isupper(prenom[0])) {
        return false;
    }
    
    // Vérifier chaque caractère pour s'assurer qu'il s'agit d'une lettre alphabétique ou d'un espace
    for (int i = 1; i < length; i++) {
        if (!islower(prenom[i]) && prenom[i] != ' ') {
            return false;
        }
    }
    
    return true;
}

int isValidGender(const char *gender) {
    const char *validGenders[] = {"homme", "femme"};
    int numValidGenders = sizeof(validGenders) / sizeof(validGenders[0]);

    for (int i = 0; i < numValidGenders; i++) {
        if (strcmp(validGenders[i], gender) == 0) {
            return 1;
        }
    }

    return 0;
}




int rech(char username[]) {
  FILE *F;
  customer account;
  F = fopen("account.txt", "r");

  if (F == NULL) {
    printf("ERREUR LORS DE L'OUVERTURE DU FICHIER.\n");
    return -1;
  }

  while (fscanf(F, "%99s ;%99s", account.username, account.password) == 2) {
    if (strcmp(account.username, username) == 0) {
      fclose(F);
      return 1;
    }
  }

  fclose(F);
  return -1;
}

int rechlogin(char username[], char password[]) {
  FILE *F;
  customer account;
  F = fopen("account.txt", "r");

  if (F == NULL) {
    printf("ERREUR LORS DE L'OUVERTURE DU FICHIER.\n");
    return -1;
  }

  while (fscanf(F, "%99s ;%99s", account.username, account.password) == 2) {
    if (strcmp(account.username, username) == 0 &&
        strcmp(account.password, password) == 0) {
      fclose(F);
      return 1;
    }
  }

  fclose(F);
  return -1;
}

void creeraccount() {
  FILE *F;
  customer account;
  char username[100];
  F = fopen("account.txt", "a");

  if (F == NULL) {
    printf("ERREUR LORS DE L'OUVERTURE DU FICHIER.\n");
    return;
  }
  if (customerCount >= MAX_CUSTOMERS) {
        printf("LE MAXIMUM DE CLIENTS A ETE ATTEINT. IMPOSSIBLE D'AJOUTER DE NOUVEAUX CLIENTS.\n");
        return;
    }
   printf("BONJOUR, POUR ACCEDER AU MODE CLIENT, VOUS DEVEZ REMPLIR LES CHAMPS SUIVANT AFIN DE VOUS CREER UN COMPTE ! ");

  printf("\n");
    printf("====================================================================");
    printf("\n");
    printf("VEUILLEZ SAISIR VOTRE PRENOM : ");
    scanf("%s", account.firstName);
    while(valider_prenom(account.firstName)==0){
      printf("PRENOM INVALIDE. VEUILLEZ SAISIR UN PRENOM VALIDE : ");
       scanf("%s", account.firstName);
    }
   printf("====================================================================");
    printf("\n");
    printf("VEUILLEZ SAISIR VOTRE NOM : ");
    scanf("%s", account.lastName);
     while(valider_prenom(account.lastName)==0){
      printf("NOM INVALIDE. VEUILLEZ SAISIR UN NOM VALIDE : ");
       scanf("%s", account.lastName);
    }

   printf("====================================================================");
    printf("\n");
    printf("VEUILLEZ SAISIR VOTRE GENRE (homme, femme) : ");
    scanf("%s", account.gender);
    while(isValidGender(account.gender)==0){
    printf("CE GENRE EST INVALIDE. VEUILLEZ SAISIR UN GENRE VALIDE (homme,femme) :  ");
    scanf("%s", account.gender);
    }

  printf("\n SAISISSEZ LE PSEUDO : ");
  scanf("%99s", username);
  while (getchar() != '\n')
    ; // Ignorer les caractères supplémentaires dans le buffer

  while (rech(username) == 1) {
    printf("\n CE PSEUDO EXISTE DEJA :");
    printf("\n SAISISSEZ UN NOUVEAU PSEUDO : ");
    scanf("%99s", username);
    while (getchar() != '\n')
      ; // Ignorer les caractères supplémentaires dans le buffer
  }

  strcpy(account.username, username);
  printf("\n SAISISSEZ LE MOT DE PASSE : ");
  scanf("%99s", account.password);
  while (getchar() != '\n')
    ; // Ignorer les caractères supplémentaires dans le buffer
   memset(account.purchaseHistory, 0, sizeof(account.purchaseHistory));

    customers[customerCount++] = account;
  saveCustomersToFile("customers.txt");
  loadCustomersFromFile("customers.txt");
printf("VOTRE COMPTE A ETE CREE AVEC SUCCES ! \n");
  printf("\n\n");
  fprintf(F, "%s ;%s\n", account.username, account.password);
  fclose(F);
}




int login() {
  FILE *F;
  customer account;

  F = fopen("account.txt", "r");
  if (F == NULL) {
    printf("ERREUR LORS DE L'OUVERTURE DU FICHIER.\n");
    return 2;
  }
 printf("A PRESENT VEUILLEZ VOUS CONNECTER EN SAISISSANT VOS IDENTIFIANTS");
  printf("\n\n");
  printf("\n Saisissez votre pseudo : ");
  scanf("%99s", account.username);
  while (getchar() != '\n')
    ; // Ignorer les caractères supplémentaires dans le buffer

  if (rech(account.username) == 1) {
    printf("\n CE PSEUDO EXISTE.");
    printf("\n SAISSISSEZ VOTRE MOT DE PASSE : ");
    scanf("%99s", account.password);
    while (getchar() != '\n')
      ; // Ignorer les caractères supplémentaires dans le buffer

    if (rechlogin(account.username, account.password) == 1) {
      printf("CONNEXION REUSSIE.\n");
      return 1;
    } else {
      printf("\n MOT DE PASSE INCORRECT.\n");
      return 0;
    }
  } else {
    printf("\n CE PSEUDO N'EXISTE PAS.\n");
    return 0;
  }

  fclose(F);
}







int isValidProductName(const char *name) {
    const char *validName[] = {"M8", "M6", "M5" ,"M4" ,"M3" ,"M2" ,"X6M" ,"X5M" ,"X4M" ,"X3M" ,"M5_CS" ,"M4_CSL", "M3_CS", "M2_CS" };
    int numValidName = sizeof(validName) / sizeof(validName[0]);

    for (int i = 0; i < numValidName; i++) {
        if (strcmp(validName[i], name) == 0) {
            return 1;
        }
    }

    return 0;
}

int isValidSize(const char *size){
  const char *validSize[]={"petit","moyen","grand"};
  int numValidSize=sizeof(validSize) / sizeof(validSize[0]);
   for (int i = 0; i < numValidSize; i++) {
        if (strcmp(validSize[i], size) == 0) {
            return 1;
        }
    }

    return 0;
}

int isValidColor(const char *color) {
    const char *validColors[] = {"bleu", "blanc", "noir"};
    int numValidColors = sizeof(validColors) / sizeof(validColors[0]);

    for (int i = 0; i < numValidColors; i++) {
        if (strcmp(validColors[i], color) == 0) {
            return 1;
        }
    }

    return 0;
}


void loadProductsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        Product newProduct;
        sscanf(line, "%[^,],%d,%d,%f,%[^,],%[^\n]", newProduct.name, &newProduct.reference, &newProduct.quantity, &newProduct.price, newProduct.color, newProduct.size);
        products[productCount++] = newProduct;
    }

    fclose(file);
}

void saveProductsToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%s,%d,%d,%.2f,%s,%s\n", products[i].name, products[i].reference, products[i].quantity, products[i].price, products[i].color, products[i].size);
    }

    fclose(file);
}


int findProductBySize(const char *productSize) {
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].size, productSize) == 0) {
            return i;
        }
    }
    return -1;
}

int findProductByColor(const char *productColor) {
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].color, productColor) == 0) {
            return i;
        }
    }
    return -1;
}

  

int findProductByName(const char *name) {
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int findProductByReference(int reference) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].reference == reference) {
            return i;
        }
    }
    return -1;
}

void displayOutOfStockProducts() {
    printf("LISTE DES PRODUITS EN RUPTURE DE STOCK :\n");
    int outOfStockCount = 0;

    for (int i = 0; i < productCount; i++) {
        if (products[i].quantity == 0) {
            printf("- %s\n", products[i].name);
            outOfStockCount++;
        }
    }

    if (outOfStockCount == 0) {
        printf("AUCUN PRODUIT EN RUPTURE DE STOCK.\n");
    }

    printf("\n");
}

void displayLowestStockProducts() {
    printf("LISTE DES 5 PRODUITS AYANT LE STOCK LE PLUS FAIBLE :\n");
    int lowestStockCount = 0;

    for (int i = 0; i < productCount; i++) {
        if (products[i].quantity > 0) {
            if (lowestStockCount < 5) {
                printf("- %s (Stock : %d)\n", products[i].name, products[i].quantity);
                lowestStockCount++;
            } else {
                break;
            }
        }
    }

    if (lowestStockCount == 0) {
        printf("AUCUN PRODUIT AVEC UN STOCK DISPONIBLE.\n");
    }

    printf("\n");
}

void displayRemainingStorageSpace() {
    int smallSizeCount = 0;
    int mediumSizeCount = 0;
    int largeSizeCount = 0;

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].size, "petit") == 0) {
            smallSizeCount++;
        } else if (strcmp(products[i].size, "moyen") == 0) {
            mediumSizeCount += 2;
        } else if (strcmp(products[i].size, "grand") == 0) {
            largeSizeCount += 4;
        }
    }

    int remainingSmallSpace = 30 - smallSizeCount;
    int remainingMediumSpace = 20 - mediumSizeCount;
    int remainingLargeSpace = 10 - largeSizeCount;
   
    printf("ESPACE DE STOCKAGE RESTANT :\n\n");
    printf("- PETIT : %d\n\n", remainingSmallSpace);
    printf("- MOYEN : %d\n\n", remainingMediumSpace);
    printf("- GRAND : %d\n\n", remainingLargeSpace);
}


int calculateRemainingStorage(Product products[], int productCount) {
    int remainingStorage = 200;
  
    for (int i = 0; i < productCount; i++) {
        if (products[i].quantity > 0) {
            int productSizeFactor;

            if (strcmp(products[i].size, "petit") == 0) {
                productSizeFactor = 1;
            } else if (strcmp(products[i].size, "moyen") == 0) {
                productSizeFactor = 2;
            } else if (strcmp(products[i].size, "grand") == 0) {
                productSizeFactor = 4;
            }

            remainingStorage -= productSizeFactor * products[i].quantity;
        }
    }

    return remainingStorage;
}

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("LE STOCK EST PLEIN. IMPOSSIBLE D'AJOUTER DE NOUVEAUX VEHICULES.\n");
       printf("\n\n");
        return;
    }

    Product newProduct;
printf("SAISISSEZ TOUR-A-TOUR LES CARACTERISTIQUES DU MODELE AJOUTE.\n");
printf("=====================================================================\n");
    printf("SAISISSEZ LE NOM DU MODELE : ");
    scanf("%s", newProduct.name);
    while(isValidProductName(newProduct.name)==0){
      printf("CE MODELE N'EXISTE PAS DANS NOTRE CATALOGUE. VEUILLEZ SAISIR UN MODELE DISPONIBLE : \n");
      scanf("%s",newProduct.name);
    }
 printf("=====================================================================\n");
    
      printf("SAISIR LA REFERENCE DU MODELE :  \n");
    scanf("%d",&newProduct.reference);
 
    while(newProduct.reference<=0){
      printf("CETTE REFERENCE N'EST PAS VALABLE. VEUILLEZ SAISIR UNE REFERENCE VALABLE : \n");
      scanf("%d",&newProduct.reference);
    }
 printf("=====================================================================\n");
    printf("SAISISSEZ LA QUANTITE QUE VOUS VOULEZ AJOUTER AU STOCK : ");
    scanf("%d", &newProduct.quantity);
  
    while(newProduct.quantity<=0){
      printf("CETTE QUANTITE EST INVALABLE OU TROP IMPORTANTE. VEUILLEZ SAISIR UNE QUANTITE VALABLE : \n");
      scanf("%d", &newProduct.quantity);
    }
 printf("=====================================================================\n");
    printf("SAISISSEZ LE PRIX CORRESPONDANT AU MODELE : ");
    scanf("%f", &newProduct.price);
 
    while(newProduct.price<=0){
      printf("CE PRIX EST INVALABLE. VEUILLEZ SAISIR UN PRIX VALABLE : ");
      scanf("%f",&newProduct.price);
    }
 printf("=====================================================================\n");
    printf("SAISISSEZ UNE COULEUR DISPONIBLE (bleu, blanc, noir) : ");
    scanf("%s", newProduct.color);
    while(isValidColor(newProduct.color)==0){
    printf("CETTE COULEUR N'EST PAS DISPONIBLE. VEUILLEZ SAISIR UNE COULEUR DISPONIBLE (bleu, blanc, noir) : ");
    scanf("%s", newProduct.color);
    }
     printf("=====================================================================\n");

    printf("SAISISSEZ UNE TAILLE DISPONIBLE (petit, moyen, grand) : ");
    scanf("%s", newProduct.size);
    while(isValidSize(newProduct.size)==0){
    printf("CETTE TAILLE N'EST PAS DISPONIBLE. VEUILLEZ SAISIR UNE TAILLE DISPONIBLE (petit, moyen, grand) : ");
    scanf("%s", newProduct.size);
    }
  printf("=====================================================================\n");
 
    products[productCount++] = newProduct;
   saveProductsToFile("products.txt");
  loadProductsFromFile("products.txt");
    
    printf("LE VEHICULE ASSOCIé AUX CARACTERISTIQUES PRECEDENTES A ETE AJOUTE AU STOCK AVEC SUCCES !\n");
  printf("\n\n\n");
}


void displayProductCatalog() {
    printf("VOICI LE CATALOGUE DES PRODUITS :\n");
    printf("\n");
    printf("NOM   REFERENCE   QUANTITE   PRIX   COULEUR   TAILLE\n");
    
    for(int i = 1; i < productCount; i++) {
        printf("%s    %d         %d         %.2f   %s        %s\n",
               products[i].name, products[i].reference, products[i].quantity,
               products[i].price, products[i].color, products[i].size);
    }
}

void displayProductStock() {
int choice;
    do {
        printf("RECHERCHER PAR :\n");
        printf("\n|1| NOM DU MODELE\n");
        printf("\n|2| NUMERO DE REFERENCE\n");
        printf("\n|0| REVENIR AU MENU DU MODE GESTION.\n\n");
        printf("VOTRE CHOIX : ");
        scanf(" %d", &choice);
        printf("\n\n");

        switch (choice) {
            case 1: {
                char productName[50];
                printf("VEUILLEZ SAISIR LE NOM DU MODELE : ");
                scanf("%s", productName);
                printf("\n");
                int index = findProductByName(productName);
                if (index != -1) {
                    printf("LE STOCK DE '%s'EST DE %d VEHICULE(S)\n", productName, products[index].quantity);
                } else {
                    printf("LE MODELE '%s' N'EST PAS DISPONIBLE DANS LE CATALOGUE.\n", productName);
                }
              printf("\n");
                break;
            }
            case 2: {
                int productReference;
                printf("VEUILLEZ SAISIR LE NUMERO DE REFERENCE DU MODELE : ");
                scanf("%d", &productReference);
                 printf("\n");
                int index = findProductByReference(productReference);
                if (index != -1) {
                    printf("LE STOCK DU MODELE AVEC LE NUMERO DE REFERENCE '%d' EST DE %d VEHICULES(S)\n", productReference, products[index].quantity);
                } else {
                    printf("AUCUN MODELE AVEC LE NUMERO DE REFERENCE '%d' N'A ETE TROUVE.\n", productReference);
                }
              printf("\n");
                break;
            }
            case 0:
                break;
            default:
                printf("CHOIX INVALIDE. VEUILLEZ RESAISIR VOTRE CHOIX.\n");
                break;
        }
    } while (choice != 0);
}

void increaseProductStock() {
    int choice;
    do {
         printf("RECHERCHER PAR :\n");
        printf("\n|1| NOM DU MODELE\n");
        printf("\n|2| NUMERO DE REFERENCE\n");
        printf("\n|0| REVENIR AU MENU DU MODE GESTION.\n\n");
        printf("VOTRE CHOIX : ");
        scanf(" %d", &choice);
        printf("\n\n");
        
        switch (choice) {
            case 1: {
                char productName[50];
                printf("VEUILLEZ SAISIR LE NOM DU MODELE : ");
                scanf("%s", productName);
                printf("\n");
                int index = findProductByName(productName);
                if (index != -1) {
                    int quantity;
                    printf("VEUILLEZ SAISIR LA QUANTITE DE VEHICULES DE CE MODELE A RAJOUTER : ");
                    scanf("%d", &quantity);
                  printf("\n");
                    products[index].quantity += quantity;
                    printf("LE STOCK DU MODELE '%s' A BIEN ETE MIS A JOUR. VOICI LE STOCK DE VEHICULES DE CE MODELE : %d\n", productName, products[index].quantity);
                } else {
                    printf("LE MODELE '%s' N'EST PAS DISPONIBLE DANS NOTRE CATALOGUE.\n", productName);
                }
              printf("\n");
                break;
            }
            case 2 : {
                int productReference;
                printf("VEUILLEZ SAISIR LE NUMERO DE REFERENCE DU MODELE : ");
                scanf("%d", &productReference);
                printf("\n");
                int index = findProductByReference(productReference);
                if (index != -1) {
                    int quantity;
                     printf("VEUILLEZ SAISIR LA QUANTITE DE VEHICULES DE CE NUMERO DE REFERENCE A RAJOUTER : ");
                    scanf("%d", &quantity);

                    products[index].quantity += quantity;
                    printf("LE STOCK DU MODELE QUI A POUR NUMERO DE REFRENCE '%d' A BIEN ETE MIS A JOUR. VOICI LE STOCK DE VEHICULES DE CE MODELE : %d\n", productReference, products[index].quantity);
                } else {
                    printf("AUCUN MODELE AVEC LE NUMERO DE REFERENCE '%d' N'A ETE TROUVE.\n", productReference);
                }
              printf("\n");
                break;
            }
            case 0:
                break;
            default:
                printf("CHOIX INVALIDE. VEUILLEZ RESAISIR VOTRE CHOIX.\n");
               printf("\n");
                break;
        }
    } while (choice != 0);
}

void manageStock() {
    int choice;
    do{
        printf("\n----- MODE GESTION -----\n\n");
        printf("=========================================================================\n");
        printf("\n");
        printf("|1| MODELE(S) EN RUPTURE DE STOCK & LES 5 MODELES LES PLUS ECOULéS \n\n");
        printf("|2| AFFICHER L'ESPACE DE STOCKAGE RESTANT\n\n");
        printf("|3| AJOUTER UN NOUVEAU MODELE\n\n");
        printf("|4| CONSULTER LE STOCK D'UN MODELE\n\n");
        printf("|5| AUGMENTER LE STOCK D'UN MODELE\n\n");
        printf("|0| QUITTER LE MODE GESTION\n\n");
        printf("=========================================================================\n");
       printf("\n");
        printf("VOTRE CHOIX : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n\n\n");
                displayOutOfStockProducts();
                displayLowestStockProducts();
                break;
            case 2:
                printf("\n\n\n");
                calculateRemainingStorage(products, productCount);
              int remainingStorage = calculateRemainingStorage(products, productCount);

    // Affichage du stockage restant
    printf("STOCKAGE RESTANT : %d\n", remainingStorage);
                break;
            case 3:
                printf("\n\n\n");
                addProduct();
                break;
            case 4:
                printf("\n\n\n");
                displayProductStock();
                break;
            case 5:
                printf("\n\n\n");
                increaseProductStock();
                break;
            case 0:
                break;
            default:
                printf("\n\n\n");
                printf("CHOIX INVALIDE. VEUILLEZ RESAISIR VOTRE CHOIX.\n");
                break;
        }
    } while (choice != 0);
}

int findCustomerByUsername(const char *username) {
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}



void displayPurchaseHistory(const Customer *customer) {
    printf("HISTORIQUE D'ACHATS :\n");
  printf("\n");
    if (customer->purchaseHistory[0] == 0 && customer->purchaseHistory[1] == 0 && customer->purchaseHistory[2] == 0) {
        printf("AUCUN ACHATS N'A ETE EFFECTUE CHEZ BMW ///M.\n");
    } else {
        for (int i = 0; i < 3; i++) {
            if (customer->purchaseHistory[i] != 0) {
                printf("-ACHAT %d : MODELE %d\n", i+1, customer->purchaseHistory[i]);
            }
        }
    }
  printf("\n");
}

void purchaseProduct(Customer *customer) {
    char productName[50];
    char productSize[20];
    char productColor[20];
    int productReference;

    printf("VEUILLEZ SAISIR LE NOM DU MODELE QUE VOUS VOULEZ ACHETER : ");
    scanf("%s", productName);

    printf("VEUILLEZ SAISIR LA TAILLE DU MODELE : ");
    scanf("%s", productSize);

    printf("VEUILLEZ SAISIR LA COULEUR DU MODELE : ");
    scanf("%s", productColor);

    printf("VEUILLEZ SAISIR LA REFERENCE DU MODELE : ");
    scanf("%d", &productReference);

    int indexBySize = findProductBySize(productSize);
    int indexByColor = findProductByColor(productColor);

    if (indexBySize != -1 && indexByColor != -1 && indexBySize == indexByColor && products[indexBySize].reference == productReference) {
        printf("LE MODELE '%s' DE TAILLE '%s' DE COULEUR '%s' AVEC LA REFERENCE '%d' EST BEL ET BIEN DISPONIBLE !\n", productName, productSize, productColor, productReference);

        int quantity;
        printf("VEUILLEZ SAISIR LE NOMBRE DE VEHICULES DE CE MODELE QUE VOUS VOULEZ ACHETER : ");
        scanf("%d", &quantity);

        if (products[indexBySize].quantity >= quantity) {
            int totalPrice = quantity * products[indexBySize].price;
            printf("ACHAT EFFECTUE AVEC SUCCES : %d %s\n", quantity, productName);
            printf("PRIX TOTAL DE L'ACHAT : %d\n", totalPrice);

            products[indexBySize].quantity -= quantity;

            for (int i = 0; i < 3; i++) {
                if (customer->purchaseHistory[i] == 0) {
                    customer->purchaseHistory[i] = products[indexBySize].reference;
                    break;
                }
            }
        } else {
            printf("LA QUANTITE DEMANDEE N'EST PAS DISPONIBLE EN STOCK.\n");
        }
    } else {
        printf("LE MODELE '%s' DE TAILLE '%s' DE COULEUR '%s' AVEC LA REFERENCE '%d' N'EST PAS DISPONIBLE DANS NOTRE CATALOGUE.\n", productName, productSize, productColor, productReference);
    }
}

void supprimeraccount() {
  char username[100];
  char password[100];

  FILE *F, *Fich;
  customer account;
  printf("ENTREZ LE PSEUDO DU COMPTE A SUPPRIMER : ");
  scanf("%99s", username);
  while (getchar() != '\n')
    ; // Ignorer les caractères supplémentaires dans le buffer
  printf("ENTREZ LE MOT DE PASSE DU COMPTE A SUPPRIMER : ");
  scanf("%99s", password);
  while (getchar() != '\n')
    ; // Ignorer les caractères supplémentaires dans le buffer

  if (rech(username) == 1) {
    if (rechlogin(username, password) == 1) {
      F = fopen("account.txt", "r");
      if (F == NULL) {
        printf("ERREUR LORS DE L'OUVERTURE DU FICHIER.\n");
        return;
      }

      Fich = fopen("tempaccount.txt", "w");
      if (Fich == NULL) {
        printf("ERREUR LORS DE L'OUVERTURE DU FICHIER TEMPORAIRE.\n");
        fclose(F);
        return;
      }

      while (fscanf(F, "%99s ;%99s", account.username, account.password) == 2) {
        if (strcmp(username, account.username) != 0) {
          fprintf(Fich, "%s ;%s\n", account.username, account.password);
        }
      }

      fclose(F);
      fclose(Fich);

      if (remove("account.txt") != 0) {
        printf("ERREUR LORS DE LA SUPPRESSION DU FICHIER.\n");
        return;
      }

      if (rename("tempaccount.txt", "account.txt") != 0) {
        printf("ERREUR LORS DU RENOMMAGE DU FICHIER TEMPORAIRE.\n");
        return;
      }
int rep;
      printf("SUPPRESSION EFFECTUEE AVEC SUCCES.\n");
      printf("Voulez-vous recreer un compte ? |1| OUI |0| NON : ");
      scanf("%d", &rep);
      if(rep==1){
      creeraccount();
    }
      if(rep==0){
        printf("DERNIERE CHANCE DE FAIRE UN ACHAT AVEC CE COMPTE ! ");
      }
      else{
        while(rep!=0 || rep!=1){
          
        
        printf("ERREUR DE SAISIE. SAISISSEZ 1 OU 0 ! :  ");
        scanf("%d",&rep);
        }
      }
   } else {
      printf(
          "MOT DE PASSE INCORRECT. SUPPRESSION ECHOUE, VEUILLEZ REESSAYER.\n");
    }
  } else {
    printf("CE PSEUDO N'EXISTE PAS.\n");
  }
}
void manageCustomers() {
    int choice;
    do {
        printf("\n----- MODE CLIENT -----\n");
        printf("\n");
        printf("======================================================\n\n");
        printf("|1| CONSULTER VOTRE HISTORIQUE D'ACHATS CHEZ BMW ///M \n\n");
        printf("|2| EFFECTUER UN ACHAT CHEZ BMW ///M \n\n");
        printf("|3| CONSULTER LE CATALOGUE DES DIFFERENTS MODELES\n\n");
        printf("|4| SUPPRIMER UN COMPTE\n\n");
        printf("|0| QUITTER LE MODE CLIENT\n\n");
        printf("======================================================");
        printf("\n\n");
        printf("VOTRE CHOIX : ");
        scanf("%d", &choice);

        switch (choice) {
            
            case 1: {
                char username[50];
              printf("\n\n");
                printf("VEUILLEZ SAISIR VOTRE NOM D'UTILISATEUR : ");
                scanf("%s", username);
              printf("\n");
                int index = findCustomerByUsername(username);
                if (index != -1) {
                    displayPurchaseHistory(&customers[index]);
                } else {
                    printf("AUCUN CLIENT AVEC LE NOM D'UTILISATEUR '%s' N'A ETE TROUVE.\n", username);
                }
              printf("\n");
                break;
            }
            case 2: {
                char username[50];
              printf("\n\n");
                printf("VEUILLEZ SAISIR VOTRE NOM D'UTILISATEUR : ");
                scanf("%s", username);

                int index = findCustomerByUsername(username);
                if (index != -1) {
                    purchaseProduct(&customers[index]);
                }
                break;
            }
          case 3 : 
            printf("\n\n");
          displayProductCatalog();
            printf("\n\n");
                break;
          case 4  :
          supprimeraccount();
        
            case 0:
                break;
            default:
                printf("\nCHOIX INVALIDE, VEUILLEZ RESAISIR VOTRE CHOIX.");
                printf("\n");
                break;
        }
    } while (choice != 0);
}
int 
accesmodegestion() {
  char password[100];
  char adminPassword[50] = "1";        // Mot de passe prédéfini pour le mode gestion

  printf("Bienvenue en mode gestion.\n");
  printf("Veuillez saisir le mot de passe pour accéder au mode gestion : ");
  scanf("%99s", password);

  if (strcmp(password, adminPassword) == 0) {
    printf("Accès au mode gestion autorisé.\n");
    manageStock();
    return(1);
    // Ajoutez ici le code pour le mode gestion
  } else {
    printf("Mot de passe incorrect. Accès refusé.\n");
    return 0;
  }
}


int main() {
  
     saveProductsToFile("products.txt");
  loadProductsFromFile("products.txt");
 saveCustomersToFile("account.txt");
  loadCustomersFromFile("account.txt");

    int modeChoice;
  int connexionChoice;
    do {
        printf("\n\n");
        printf("================================================================\n");
        printf("   ___    __  ___  _      __          __     __     __   __  ___\n");
        printf("  / _ )  /  |/  / | | /| / /        _/_/   _/_/   _/_/  /  |/  /\n");
        printf(" / _  | / /|_/ /  | |/ |/ /       _/_/   _/_/   _/_/   / /|_/ / \n");
        printf("/____/ /_/  /_/   |__/|__/       /_/    /_/    /_/    /_/  /_/  \n");
        printf("\n");
        printf("================================================================\n");
        printf("\n\n\n");    
printf("=====================================================================================\n");
      printf("\n\n\n");
        printf("                      _.-=\"_-         _\n");
    printf("                 _.-=\"   _-          | ||\"\"\"\"\"\"\"\"---._______     __..\n");
    printf("         ___.===\"\"\"-.______-,,,,,,,,,,,,`-''----\" \"\"\"\"\"\"\"\"\"       \"\"\"\"\"\"\"\"  __'\n");
    printf("  __.--\"\"     __        ,'                   o \\           __        [__|\n");
    printf("_-\"=======.--\"\"  \"\"--.=================================.--\"\"  \"\"--.=======:\n");
    printf("]          [w] : /        \\ : |========================|    : /        \\ :  [w] :\n");
    printf("V___________:|          |: |========================|    :|          |:   _-\"\n");
    printf(" V__________: \\        / :_|=======================/_____: \\        / :__-\"\n");
    printf("  -----------'  \"-____-\"  `-------------------------------'  \"-____-\"\n");
             printf("\n\n\n"); printf("=====================================================================================\n");
        printf("\n\n\n");
        printf("========================\n");
        printf("\n");
        printf("|1| MODE GESTION\n\n");
        printf("|2| MODE CLIENT\n\n");
        printf("|0| QUITTER L'APPLICATION\n");
        printf("\n");
        printf("========================\n\n");
        printf("VOTRE CHOIX : ");
        scanf("%d", &modeChoice);
        printf("\n");
      
        switch (modeChoice) {
            case 1:
               accesmodegestion();
              
                break;
            case 2:
                printf("AVEZ-VOUS DEJA UN COMPTE ?-->|1| OUI |2| NON");
              printf("\n");
              printf("VOTRE CHOIX : ");
              scanf("%d", &connexionChoice);
              if(connexionChoice==1){
                 if(login()){
                  manageCustomers();
                }
              else{
                login();
              }
              }
              
              if(connexionChoice==2){ 
                creeraccount(

        
                );
                if(login()){
                  manageCustomers();
                }
              else{
                login();
              }
              }
          
              else if(connexionChoice!=2 && connexionChoice!=1){
                printf("CHOIX INVALIDE, VEUILLEZ RESAISIR VOTRE CHOIX : ");
                scanf("%d",&connexionChoice);
              }
                break;
            case 0:
                printf("AU REVOIR ! A BIENTOT ;)");
                break;
            default:
                printf("CHOIX INVALIDE, VEUILLEZ RESAISIR VOTRE CHOIX.");
                break;
        }
    } while (modeChoice != 0);

     saveProductsToFile("products.txt");
  loadProductsFromFile("products.txt");
 saveCustomersToFile("account.txt");
  loadCustomersFromFile("account.txt");
    return 0;
}
