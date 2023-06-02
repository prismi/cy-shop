#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 200
#define MAX_CUSTOMERS 200
// Plafond de clients & produits
typedef struct {
  char name[50];
  int reference;
  int quantity;
  float price;
  char color[20];
  char size[20];
} Product;
// Structure produits
typedef struct {
  char firstName[50];
  char lastName[50];
  char username[50];
  char gender[10];
  char password[50];
  int purchaseHistorySize;
  int *purchaseHistory;
} Customer;
// Structure clients
typedef struct {
  char firstName[50];
  char lastName[50];
  char username[100];
  char password[100];
  char gender[10];
  int purchaseHistory[3];
} customer;
// Structure comptes clients
void loadCustomersFromFile(const char *filename, Customer customers[],
                           int *customerCount) {

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
    return;
  }

  char line[100];
  while (fgets(line, sizeof(line), file) != NULL) {
    Customer newCustomer;
    newCustomer.purchaseHistory = malloc(sizeof(int) * 3);
    sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d",
           newCustomer.firstName, newCustomer.lastName, newCustomer.username,
           newCustomer.gender, newCustomer.password,
           &newCustomer.purchaseHistory[0], &newCustomer.purchaseHistory[1],
           &newCustomer.purchaseHistory[2]);
    customers[(*customerCount)++] = newCustomer;
  }
  fclose(file);
}
// Charger des fiches clients
void saveCustomersToFile(const char *filename, const Customer customers[],
                         int *customerCount) {
  FILE *file = fopen(filename, "a");

  if (file == NULL) {
    printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
    return;
  }

  for (int i = 0; i < *customerCount; i++) {
    fprintf(file, "%s,%s,%s,%s,%s,%d,%d,%d\n", customers[i].firstName,
            customers[i].lastName, customers[i].username, customers[i].gender,
            customers[i].password, customers[i].purchaseHistory[0],
            customers[i].purchaseHistory[1], customers[i].purchaseHistory[2]);
  }

  fclose(file);
}
// Sauvegarder des fiches clients
void loadProductsFromFile(const char *filename, Product products[],
                          int *productCount) {

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
    return;
  }
  char line[100];
  while (fgets(line, sizeof(line), file) != NULL) {
    Product newProduct;
    sscanf(line, "%[^,],%d,%d,%f,%[^,],%[^\n]", newProduct.name,
           &newProduct.reference, &newProduct.quantity, &newProduct.price,
           newProduct.color, newProduct.size);
    products[(*productCount)++] = newProduct;
  }
  fclose(file);
}

void saveProductsToFile(const char *filename, const Product products[],
                        int productCount) {

  FILE *file = fopen(filename, "a");
  if (file == NULL) {
    printf("IMPOSSIBLE D'OUVRIR LE FICHIER '%s'.\n", filename);
    return;
  }

  for (int i = 0; i < productCount; i++) {
    fprintf(file, "%s,%d,%d,%.2f,%s,%s\n", products[i].name,
            products[i].reference, products[i].quantity, products[i].price,
            products[i].color, products[i].size);
  }
  fclose(file);
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

bool valider_prenom(const char *prenom) {
  int length = strlen(prenom);
  // Vérifier si la chaîne est vide
  if (length == 0) {
    return false;
  }

  // Vérifier si le premier caractère est une lettre majuscule
  if (!isupper(prenom[0])) {
    return false;
  }

  // Vérifier chaque caractère pour s'assurer qu'il s'agit d'une lettre

  // alphabétique ou d'un espace

  for (int i = 1; i < length; i++) {
    if (!islower(prenom[i]) && prenom[i] != ' ') {
      return false;
    }
  }
  return true;
}
int isValidProductName(const char *name) {
  const char *validName[] = {"M8",    "M6",     "M5",    "M4",   "M3",
                             "M2",    "X6M",    "X5M",   "X4M",  "X3M",
                             "M5_CS", "M4_CSL", "M3_CS", "M2_CS"};

  int numValidName = sizeof(validName) / sizeof(validName[0]);
  for (int i = 0; i < numValidName; i++) {
    if (strcmp(validName[i], name) == 0) {
      return 1;
    }
  }

  return 0;
}

int isValidSize(const char *size) {
  const char *validSize[] = {"petit", "moyen", "grand"};
  int numValidSize = sizeof(validSize) / sizeof(validSize[0]);
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

int isReferenceUnique(int reference, Product products[], int productCount) {
  for (int i = 0; i < productCount; i++) {
    if (products[i].reference == reference) {
      return 0; // La référence existe déjà
    }
  }
  return 1; // La référence est unique
}

int findProductByNameAndReference(const char *name, int reference,
                                  int productCount, Product products[]) {

  for (int i = 0; i < productCount; i++) {
    if (strcmp(products[i].name, name) == 0 &&
        products[i].reference == reference) {
      return i; // Produit trouvé
    }
  }
  return -1; // Produit non trouvé
}

int findProductBySize(const Product *products, int productCount,
                      const char *productSize) {
  for (int i = 0; i < productCount; i++) {
    if (strcmp(products[i].size, productSize) == 0) {
      return i;
    }
  }
  return -1;
}

int findProductByColor(const Product *products, int productCount,
                       const char *productColor) {
  for (int i = 0; i < productCount; i++) {
    if (strcmp(products[i].color, productColor) == 0) {
      return i;
    }
  }
  return -1;
}

int findCustomerByUsername(Customer *customers, int customerCount,
                           const char *username) {
  for (int i = 0; i < customerCount; i++) {
    if (strcmp(customers[i].username, username) == 0) {
      return i;
    }
  }
  return -1;
}

void addProduct(Product products[], int *productCount) {
  if (*productCount >= MAX_PRODUCTS) {
    printf("LE STOCK EST PLEIN. IMPOSSIBLE D'AJOUTER DE NOUVEAUX VEHICULES.\n");
    printf("\n\n");
    return;
  }
  Product newProduct;

  printf("SAISISSEZ TOUR-A-TOUR LES CARACTERISTIQUES DU MODELE AJOUTE.\n");
  printf("====================================================================="
         "\n");
  printf("SAISISSEZ LE NOM DU MODELE : ");
  scanf("%49s", newProduct.name);

  while (isValidProductName(newProduct.name) == 0) {
    printf("CE MODELE N'EXISTE PAS DANS NOTRE CATALOGUE. VEUILLEZ SAISIR UN "
           "MODELE DISPONIBLE : \n");
    scanf("%49s", newProduct.name);
  }

  printf("====================================================================="
         "\n");
  printf("SAISIR LA REFERENCE DU MODELE :  \n");
  scanf("%d", &newProduct.reference);

  while (newProduct.reference <= 0 ||
         isReferenceUnique(newProduct.reference, products,
                           newProduct.reference) == 0) {
    if (newProduct.reference <= 0) {
      printf("CETTE REFERENCE N'EST PAS VALABLE. VEUILLEZ SAISIR UNE "
             "REFERENCE "
             "VALABLE : \n");
    } else {
      printf("CETTE REFERENCE EXISTE DEJA. VEUILLEZ SAISIR UNE REFERENCE "
             "UNIQUE : \n");
    }
    scanf("%d", &newProduct.reference);
  }

  printf("====================================================================="
         "\n");
  printf("SAISISSEZ LA QUANTITE QUE VOUS VOULEZ AJOUTER AU STOCK : ");
  scanf("%d", &newProduct.quantity);

  while (newProduct.quantity <= 0) {
    printf("CETTE QUANTITE EST INVALABLE OU TROP IMPORTANTE. VEUILLEZ SAISIR "
           "UNE QUANTITE VALABLE : \n");
    scanf("%d", &newProduct.quantity);
  }

  printf("====================================================================="
         "\n");
  printf("SAISISSEZ LE PRIX CORRESPONDANT AU MODELE : ");
  scanf("%f", &newProduct.price);

  while (newProduct.price <= 0) {
    printf("CE PRIX EST INVALABLE. VEUILLEZ SAISIR UN PRIX VALABLE : ");
    scanf("%f", &newProduct.price);
  }

  printf("====================================================================="
         "\n");

  printf("SAISISSEZ UNE COULEUR DISPONIBLE (bleu, blanc, noir) : ");
  scanf("%19s", newProduct.color);
  while (isValidColor(newProduct.color) == 0) {
    printf("CETTE COULEUR N'EST PAS DISPONIBLE. VEUILLEZ SAISIR UNE COULEUR "
           "DISPONIBLE (bleu, blanc, noir) : ");
    scanf("%19s", newProduct.color);
  }

  printf("====================================================================="
         "\n");

  printf("SAISISSEZ UNE TAILLE DISPONIBLE (petit, moyen, grand) : ");
  scanf("%19s", newProduct.size);
  while (isValidSize(newProduct.size) == 0) {
    printf("CETTE TAILLE N'EST PAS DISPONIBLE. VEUILLEZ SAISIR UNE TAILLE "
           "DISPONIBLE (petit, moyen, grand) : ");
    scanf("%19s", newProduct.size);
  }

  printf("====================================================================="
         "\n");

  products[(*productCount)++] = newProduct;

  saveProductsToFile("products.txt", products, *productCount);
  printf("LE VEHICULE ASSOCIE AUX CARACTERISTIQUES PRECEDENTES A ETE AJOUTE AU "
         "STOCK AVEC SUCCES !\n");
  printf("\n\n\n");
}

void increaseProductStock(Product products[], int productCount) {

  char productName[50];
  int productReference;
  int quantity;

  printf("SAISISSEZ LE NOM DU MODELE : ");
  scanf("%49s", productName);
  printf("\n");
  printf("SAISISSEZ LA REFERENCE DU MODELE : ");
  scanf("%d", &productReference);
  printf("\n");
  int index = findProductByNameAndReference(productName, productReference,
                                            productCount, products);

  if (index != -1) {
    printf("VEUILLEZ SAISIR LA QUANTITE DE VEHICULES DE CE MODELE A RAJOUTER "
           ": ");
    scanf("%d", &quantity);
    printf("\n");
    products[index].quantity += quantity;
    printf("LE STOCK DU MODELE '%s' A BIEN ETE MIS A JOUR. VOICI LE STOCK DE "
           "VEHICULES DE CE MODELE : %d\n",
           productName, products[index].quantity);
    printf("\n");

  } else {
    printf("LE MODELE AVEC LE NOM '%s' ET LA REFERENCE '%d' N'A PAS ETE "
           "TROUVE.\n",
           productName, productReference);
    printf("\n");
  }
  saveProductsToFile("products.txt", products, productCount);
}
void displayProductStock(const char *productName, int productReference,
                         Product products[], int productCount) {

  if (productName != NULL && productReference > 0) {
    // Vérifier l'existence du nom et de la référence
    int index = findProductByNameAndReference(productName, productReference,
                                              productCount, products);

    if (index != -1) {
      printf("LE STOCK DU MODELE '%s' AVEC LE NUMERO DE REFERENCE '%d' EST DE "
             "%d VEHICULE(S)\n",
             productName, productReference, products[index].quantity);
    } else {
      printf("AUCUN MODELE CORRESPONDANT AU NOM '%s' ET AU NUMERO DE REFERENCE "
             "'%d' N'A ETE TROUVE.\n",
             productName, productReference);
    }
  } else if (productName != NULL) {

    // Vérifier l'existence du nom
    int index = findProductByNameAndReference(productName, productReference,
                                              productCount, products);

    if (index != -1) {
      printf("LE STOCK DU MODELE '%s' EST DE %d VEHICULE(S)\n", productName,
             products[index].quantity);
    } else {
      printf("LE MODELE '%s' N'EST PAS DISPONIBLE DANS LE CATALOGUE.\n",
             productName);
    }
  } else if (productReference > 0) {

    // Vérifier l'existence de la référence

    int index = findProductByNameAndReference(productName, productReference,
                                              productCount, products);
    if (index != -1) {
      printf("LE STOCK DU MODELE AVEC LE NUMERO DE REFERENCE '%d' EST DE %d "
             "VEHICULE(S)\n",
             productReference, products[index].quantity);
    } else {
      printf("AUCUN MODELE AVEC LE NUMERO DE REFERENCE '%d' N'A ETE TROUVE.\n",
             productReference);
    }
  } else {

    printf("AUCUN PARAMETRE VALABLE FOURNI. VEUILLEZ SAISIR UN NOM DE MODELE "
           "OU UN NUMERO DE REFERENCE.\n");
  }
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

void displayOutOfStockProducts(Product products[], int productCount) {
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

void displayLowestStockProducts(Product products[], int productCount) {
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

void manageStock(Product products[], int productCount) {
  int choice;
  do {
    printf("\n----- MODE GESTION -----\n\n");
    printf("==================================================================="
           "======\n");

    printf("\n");
    printf("|1| MODELE(S) EN RUPTURE DE STOCK & LES 5 MODELES LES PLUS "
           "ECOULES\n\n");
    printf("|2| AFFICHER L'ESPACE DE STOCKAGE RESTANT\n\n");
    printf("|3| AJOUTER UN NOUVEAU MODELE\n\n");
    printf("|4| CONSULTER LE STOCK D'UN MODELE\n\n");
    printf("|5| AUGMENTER LE STOCK D'UN MODELE\n\n");
    printf("|0| QUITTER LE MODE GESTION\n\n");

    printf("==================================================================="
           "======\n");
    printf("\n");
    printf("VOTRE CHOIX : ");
    scanf("%d", &choice);
    switch (choice) {

    case 1:
      printf("\n\n\n");
      displayOutOfStockProducts(products, productCount);
      displayLowestStockProducts(products, productCount);
      break;

    case 2:
      printf("\n\n\n");
      int remainingStorage = calculateRemainingStorage(products, productCount);
      printf("STOCKAGE RESTANT : %d\n", remainingStorage);
      break;
    case 3:
      printf("\n\n\n");
      addProduct(products, &productCount);
      break;
    case 4:
      printf("\n\n\n");

      char productName[50];
      int productReference;

      printf("VEUILLEZ SAISIR LE NOM DU MODELE : ");
      scanf("%s", productName);
      printf("VEUILLEZ SAISIR LE NUMERO DE REFERENCE DU MODELE : ");
      scanf("%d", &productReference);
      printf("\n");
      displayProductStock(products, productCount, productName,
                          productReference);
      break;
    case 5:
      printf("\n\n\n");
      increaseProductStock(products, productCount);
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

int accessModeGestion(Product products[], int productCount) {

  char password[100];
  char adminPassword[50] = "1"; // Mot de passe prédéfini pour le mode gestion

  printf("Bienvenue en mode gestion.\n");
  printf("Veuillez saisir le mot de passe pour accéder au mode gestion : ");
  scanf("%99s", password);

  if (strcmp(password, adminPassword) == 0) {
    printf("Accès au mode gestion autorisé.\n");
    manageStock(products, productCount);
    return 1;

  } else {
    printf("Mot de passe incorrect. Accès refusé.\n");
    return 0;
  }
}

int rech(Customer customers[], int customerCount, char username[]) {
  for (int i = 0; i < customerCount; i++) {
    if (strcmp(customers[i].username, username) == 0) {
      return 1;
    }
  }
  return 0;
}

int rechlogin(Customer customers[], int customerCount, char username[],

              char password[]) {

  for (int i = 0; i < customerCount; i++) {

    if (strcmp(customers[i].username, username) == 0 &&
        strcmp(customers[i].password, password) == 0) {
      return 1;
    }
  }
  return 0;
}

void creerAccount(Customer customers[], int *customerCount) {
  FILE *F;
  Customer account;
  char username[100];

  F = fopen("customers.txt", "a");

  if (F == NULL) {
    printf("ERREUR LORS DE L'OUVERTURE DU FICHIER.\n");
    return;
  }

  if (*customerCount >= MAX_CUSTOMERS) {
    printf("LE MAXIMUM DE CLIENTS A ETE ATTEINT. IMPOSSIBLE D'AJOUTER DE "
           "NOUVEAUX CLIENTS.\n");
    fclose(F);
    return;
  }

  printf("BONJOUR, POUR ACCEDER AU MODE CLIENT, VOUS DEVEZ REMPLIR LES CHAMPS "
         "SUIVANT AFIN DE VOUS CREER UN COMPTE !\n");

  printf("\n");
  printf(
      "====================================================================");

  printf("\n");
  printf("VEUILLEZ SAISIR VOTRE PRENOM : ");
  scanf("%s", account.firstName);
  while (!valider_prenom(account.firstName)) {
    printf("PRENOM INVALIDE. VEUILLEZ SAISIR UN PRENOM VALIDE : ");
    scanf("%s", account.firstName);
  }
  printf(
      "====================================================================");

  printf("\n");
  printf("VEUILLEZ SAISIR VOTRE NOM : ");
  scanf("%s", account.lastName);
  while (!valider_prenom(account.lastName)) {
    printf("NOM INVALIDE. VEUILLEZ SAISIR UN NOM VALIDE : ");
    scanf("%s", account.lastName);
  }

  printf(
      "====================================================================");

  printf("\n");
  printf("VEUILLEZ SAISIR VOTRE GENRE (homme, femme) : ");
  scanf("%s", account.gender);
  while (!isValidGender(account.gender)) {
    printf("CE GENRE EST INVALIDE. VEUILLEZ SAISIR UN GENRE VALIDE (homme, "
           "femme) : ");
    scanf("%s", account.gender);
  }

  printf("\n SAISISSEZ LE PSEUDO : ");
  scanf("%99s", username);
  while (getchar() != '\n') {
    // Ignorer les caractères supplémentaires dans le buffer
  }

  while (rech(customers, *customerCount, username) == 1) {
    printf("\n CE PSEUDO EXISTE DEJA :");
    printf("\n SAISISSEZ UN NOUVEAU PSEUDO : ");
    scanf("%s", username);
    while (getchar() != '\n') {
      // Ignorer les caractères supplémentaires dans le buffer
    }
  }

  strcpy(account.username, username);

  printf("\n SAISISSEZ LE MOT DE PASSE : ");
  scanf("%s", account.password);
  while (getchar() != '\n') {
    // Ignorer les caractères supplémentaires dans le buffer
  }

  memset(account.purchaseHistory, 0, sizeof(account.purchaseHistory));

  customers[*customerCount] = account;
  (*customerCount)++;

  printf("VOTRE COMPTE A ETE CREE AVEC SUCCES ! \n");
  printf("\n\n");

  fprintf(F, "%s ;%s\n", account.username, account.password);

  fclose(F);

  saveCustomersToFile("customers.txt", customers, *customerCount);
  saveCustomersToFile("account.txt", customers, *customerCount);
}

void displayPurchaseHistory(const Customer *customer) {
  printf("HISTORIQUE D'ACHATS :\n");
  printf("\n");

  if (customer->purchaseHistory[0] == 0 && customer->purchaseHistory[1] == 0 &&
      customer->purchaseHistory[2] == 0) {
    printf("AUCUN ACHAT N'A ETE EFFECTUE CHEZ BMW ///M.\n");

  } else {
    for (int i = 0; i < 3; i++) {
      if (customer->purchaseHistory[i] != 0) {
        printf("- ACHAT %d : MODELE %d\n", i + 1, customer->purchaseHistory[i]);
      }
    }
  }
  printf("\n");
}

void displayProductCatalog(const Product *products, int productCount) {
  printf("VOICI LE CATALOGUE DES PRODUITS :\n");
  printf("\n");
  printf("NOM   REFERENCE   QUANTITE   PRIX   COULEUR   TAILLE\n");

  for (int i = 0; i < productCount; i++) {
    printf("%s    %d         %d         %.2f   %s        %s\n",
           products[i].name, products[i].reference, products[i].quantity,
           products[i].price, products[i].color, products[i].size);
  }
}

void purchaseProduct(Customer *customer, const Product *products,
                     int productCount) {

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

  // Vérification de la validité du nom, de la couleur et de la taille

  if (!isValidProductName(productName) || !isValidColor(productColor) ||
      !isValidSize(productSize)) {
    printf("LES DONNEES SAISIES NE SONT PAS VALABLES.\n");
    return;
  }

  int indexBySize = findProductBySize(products, productCount, productSize);

  int indexByColor = findProductByColor(products, productCount, productColor);

  if (indexBySize != -1 && indexByColor != -1 && indexBySize == indexByColor &&
      products[indexBySize].reference == productReference) {
    printf("LE MODELE '%s' DE TAILLE '%s' DE COULEUR '%s' AVEC LA REFERENCE "
           "'%d' EST BEL ET BIEN DISPONIBLE !\n",
           productName, productSize, productColor, productReference);

    int quantity;
    printf("VEUILLEZ SAISIR LE NOMBRE DE VEHICULES DE CE MODELE QUE VOUS "
           "VOULEZ ACHETER : ");
    scanf("%d", &quantity);

    if (products[indexBySize].quantity >= quantity) {
      int totalPrice = quantity * products[indexBySize].price;
      printf("ACHAT EFFECTUE AVEC SUCCES : %d %s\n", quantity, productName);
      printf("PRIX TOTAL DE L'ACHAT : %d\n", totalPrice);
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

    printf("LE MODELE '%s' DE TAILLE '%s' DE COULEUR '%s' AVEC LA "
           "REFERENCE'%d' N'EST PAS DISPONIBLE DANS NOTRE CATALOGUE.\n",
           productName, productSize, productColor, productReference);
  }
}

void supprimeraccount(const char *username, const char *password,

                      int customerCount) {

  FILE *F, *Fich;
  Customer account[200];

  if (rech(account, customerCount, username) == 1) {
    if (rechlogin(account, customerCount, username, password) == 1) {

      F = fopen("account.txt", "a");
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

      for (int i = 0; i < customerCount; i++) {
        if (strcmp(username, account[i].username) != 0) {
          fprintf(Fich, "%s ;%s\n", account[i].username, account[i].password);
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

      printf("SUPPRESSION EFFECTUEE AVEC SUCCES.\n");
      printf("Voulez-vous recreer un compte ? |1| OUI |0| NON : ");

      int rep;
      scanf("%d", &rep);

      if (rep == 1) {
        creerAccount(account, &customerCount);
      } else if (rep == 0) {
        printf("DERNIERE CHANCE DE FAIRE UN ACHAT AVEC CE COMPTE ! ");
      } else {
        while (rep != 0 && rep != 1) {
          printf("ERREUR DE SAISIE. SAISISSEZ 1 OU 0 ! :  ");
          scanf("%d", &rep);
        }
      }
    } else {
      printf("MOT DE PASSE INCORRECT. SUPPRESSION ECHOUEE, VEUILLEZ "
             "REESSAYER.\n");
    }
  } else {
    printf("CE PSEUDO N'EXISTE PAS.\n");
  }
}

void manageCustomers(Customer *customers, int customerCount, Product *products,
                     int productCount) {
  int choice;
  do {
    printf("\n----- MODE CLIENT -----\n\n");
    printf("======================================================\n");
    printf("|1| CONSULTER VOTRE HISTORIQUE D'ACHATS CHEZ BMW ///M\n");
    printf("|2| EFFECTUER UN ACHAT CHEZ BMW ///M\n");
    printf("|3| CONSULTER LE CATALOGUE DES DIFFERENTS MODELES\n");
    printf("|4| SUPPRIMER UN COMPTE\n");
    printf("|0| QUITTER LE MODE CLIENT\n");
    printf("======================================================\n\n");
    printf("VOTRE CHOIX : ");
    scanf("%d", &choice);

    char username1[50];
    char password1[100];

    switch (choice) {
    case 1: {
      char username[50];
      printf("\n\n");
      printf("VEUILLEZ SAISIR VOTRE NOM D'UTILISATEUR : ");
      scanf("%s", username);
      printf("\n");

      int index = findCustomerByUsername(customers, customerCount, username);
      if (index != -1) {
        displayPurchaseHistory(&customers[index]);
      } else {
        printf("AUCUN CLIENT AVEC LE NOM D'UTILISATEUR '%s' N'A ETE TROUVE.\n",
               username);
      }
      printf("\n");
      break;
    }

    case 2: {
      char username[50];
      printf("\n\n");
      printf("VEUILLEZ SAISIR VOTRE NOM D'UTILISATEUR : ");
      scanf("%s", username);
      int index = findCustomerByUsername(customers, customerCount, username);
      if (index != -1) {
        purchaseProduct(&customers[index], products, productCount);
      }
      break;
    }
    case 3:
      printf("\n\n");
      displayProductCatalog(products, productCount);
      printf("\n\n");
      break;
    case 4:
      printf("\n\n");
      printf("ENTREZ LE PSEUDO DU COMPTE A SUPPRIMER : ");
      scanf("%s", username1);
      while (getchar() != '\n')

        ; // Ignorer les caractères supplémentaires dans le buffer
      printf("ENTREZ LE MOT DE PASSE DU COMPTE A SUPPRIMER : ");
      scanf("%99s", password1);
      while (getchar() != '\n')
        ; // Ignorer les caractères supplémentaires dans le buffer
      supprimeraccount(username1, password1, customerCount);
      break;
    case 0:
      break;
    default:
      printf("\nCHOIX INVALIDE, VEUILLEZ RESAISIR VOTRE CHOIX.\n\n");
      break;
    }
  } while (choice != 0);
}

int main() {

  Product products[MAX_PRODUCTS];
  int productCount = 0;
  Customer customers[MAX_CUSTOMERS];
  int *customerCount = 0;
  int modeChoice;
  int connexionChoice;

  loadProductsFromFile("products.txt", products, &productCount);
  loadCustomersFromFile("customers.txt", customers, &customerCount);
  loadCustomersFromFile("account.txt", customers, &customerCount);

  do {
    printf("\n\n");
    printf(

        "================================================================\n");
    printf(

        "   ___    __  ___  _      __          __     __     __   __  ___\n");
    printf(

        "  / _ )  /  |/  / | | /| / /        _/_/   _/_/   _/_/  /  |/  /\n");
    printf(

        " / _  | / /|_/ /  | |/ |/ /       _/_/   _/_/   _/_/   / /|_/ / \n");
    printf(

        "/____/ /_/  /_/   |__/|__/       /_/    /_/    /_/    /_/  /_/  \n");
    printf("\n");
    printf(

        "================================================================\n");
    printf("\n\n\n");
    printf("==================================================================="
           "==================\n");
    printf("\n\n\n");
    printf("                      _.-=\"_-         _\n");
    printf("                 _.-=\"   _-          | "

           "||\"\"\"\"\"\"\"\"---._______     __..\n");
    printf("         ___.===\"\"\"-.______-,,,,,,,,,,,,`-''----\" "

           "\"\"\"\"\"\"\"\"\"       \"\"\"\"\"\"\"\"  __'\n");
    printf("  __.--\"\"     __        ,'                   o \\           __   "

           "     [__|\n");
    printf(

        "_-\"=======.--\"\"  \"\"--.=================================.--\"\" "
        " "

        "\"\"--.=======:\n");
    printf("]          [w] : /        \\ : |========================|    : /   "

           "     \\ :  [w] :\n");
    printf("V___________:|          |: |========================|    :|        "
           "  |:   _-\"\n");
    printf(" V__________: \\        / :_|=======================/_____: \\     "

           "   / :__-\"\n");
    printf("  -----------'  \"-____-\"  `-------------------------------'  "
           "\"-____-\"\n");
    printf("\n\n\n");
    printf("==================================================================="
           "==================\n");
    printf("\n\n\n");
    printf("========================\n");
    printf("\n");
    printf("|1| MODE GESTION\n\n");
    printf("|2| MODE CLIENT\n\n");
    printf("|0| QUITTER L'APPLICATION\n");
    printf("\n");
    printf("========================\n\n");
    printf("VOTRE CHOIX : ");
    while (scanf("%d", &modeChoice) != 1) {
      printf("Saisie invalide. Veuillez entrer un entier : ");
      while (getchar() != '\n')
        ; // Vide le tampon d'entrée
    }
    printf("\n");

    switch (modeChoice) {
    case 1:
      accessModeGestion(products, productCount);
      break;
    case 2:
      printf("AVEZ-VOUS DEJA UN COMPTE ?-->|1| OUI |2| NON\n");
      printf("VOTRE CHOIX : ");
      scanf("%d", &connexionChoice);
      if (connexionChoice == 1) {
        if (login(customers, *customerCount)) {
          manageCustomers(customers, *customerCount, products, productCount);
        } else {
          login(customers, *customerCount);
        }
      } else if (connexionChoice == 2) {
        creerAccount(customers, &customerCount);
        if (login(customers, *customerCount)) {
          manageCustomers(customers, *customerCount, products, productCount);
        } else {
          login(customers, *customerCount);
        }
      } else {
        printf("CHOIX INVALIDE, VEUILLEZ RESSAISIR VOTRE CHOIX : ");
        while (scanf("%d", &connexionChoice) != 1) {
          printf("Saisie invalide. Veuillez entrer un entier : ");
          while (getchar() != '\n')
            ; // Vide le tampon d'entrée
        }
      }
      break;
    case 0:
      printf("AU REVOIR ! A BIENTOT ;)\n");
      break;
    default:
      printf("CHOIX INVALIDE, VEUILLEZ RESSAISIR VOTRE CHOIX.\n");
      break;
    }
  } while (modeChoice != 0);
  return 0;
}
