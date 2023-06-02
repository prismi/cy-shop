CY-Shop

Bonjour et bienvenue dans le programme de Rayan HUSSEIN, Adel SMAILI et de Prismithan ANANTHAKUMAR, élèves de la MI-3!

Notre projet de gestion de stocks propose l'achat de voitures sportives de la marque allemande BMW pour les acheteurs. Comme demandé, il comporte bien un mode gestion et un mode achat dans lesquelles  les consignes du cahier des charges sont inclues. Comme nous l'avons expliqué lors de la soutenance, à cause d'une erreur de segmentation que nous n'avons pas pu régler, nous sommes dans l'obligation de vous rendre deux programmes différents afin que vous puissez tester toutes les fonctionnalités proposées. En ce qui concerne le depôt tardif, ceci s'explique par le fait que nous avions attendu de vous parler de notre problème rencontré avec notre projet avant de le restituer comme il se doit, mais nous tenons à vous informer que nous avions quand même rendu un code source avant la date butoire.

Le premier programme, simplement nommé "cy-shop_achat.c" est le programme à utiliser pour accèder au mode clients. Ce programme doit être utilisé avec le fichier "products.txt" dans lequel toutes les voitures à la vente sont indiquées. Pour accéder au mode achat, il faut d'abord créer un compte en indiquant le prénom et le nom de famille (la première lettre doit être en majuscule!), le genre, un pseudo ainsi qu'un mot de passe. Pour se connecter il suffira de renseigner le pseudo et le mot de passe. Il vous faura ensuite vous connecter et vous aurez alors accès à l'ensemble des fonctionnalités. Dans ce programme là, le mode gestion fonctionne mais pas à la perfection, c'est pour cela que nous vous invitons à utiliser l'autre programme.

Ainsi, en ce qui concerne l'accès au mode gestion, vous devez utiliser le programme nommé "cy-shop_gestion.c". Vous devez également l'utiliser en ouvrant le fichier "products.txt" afin de tester toutes les fonctions.Pour accéder au mode gestion et le quitter, il faut entrer un mot de passe et celui-ci est "1". En ce qui concerne l'ajout d'un produit, vous devez choisir un nom de produit prédéfini qui sont inclus dans la fonction "isValidname". Cependant, il est impossible d'accéder au mode achat ici, en raison d'une erreur de segmentation. Ce programme doit également être utilisé avec le fichier "products.txt".



Le makefile, bien qu'il ne sera pas de grande utilité (programme non-modulé), est également présent. Le lancement des programmes est possible en compilant le programme sur le système d'exploitation Ubuntu.


Nous avons utilisé Visual Studio Code ainsi que Replit pour écrire ce projet, puis il a été testé sur des ordinateurs tournant sur Ubuntu. Formant un trio de jeunes novices en informatique, nous avons conscience que notre programme n'est pas le plus fonctionnel, mais nous espèrons tout de même qu'il vous plaira quand même, bonne découverte ;).

PS: il y a un fichier nommé "cy-shop.c", veuillez ne pas y tenir compte, il s'agit juste d'un code publié pour prouver que nous avions bien rendu quelque chose avant la date limite fixée.
