#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>

struct entry_s{
	char *key;
	char *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s{
	int size;
	struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;

//Create a new hashtable.
	hashtable_t *ht_create( int size ){
	hashtable_t *hashtable = NULL;
	int i;
	if( size < 1 ) return NULL;
//Allocate the table itself.
	if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ){
	return NULL;
	}
//Allocate pointers to the head nodes.
	if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ){
	return NULL;
	}
	for( i = 0; i < size; i++ ){
	hashtable->table[i] = NULL;
	}
	hashtable->size = size;
	return hashtable;
	}
//Hash a string for a particular hash table.
	int ht_hash( hashtable_t *hashtable, char *key ){
	unsigned long int hashval;
	int i = 0;
//Convert our string to an integer.
	while( hashval < ULONG_MAX && i < strlen( key ) ){
	hashval = hashval << 8;
	hashval += key[ i ];
	i++;
	}
	return hashval % hashtable->size;
	}
//Create a key-value pair.
	entry_t *ht_newpair( char *key, char *value ){
	entry_t *newpair;
	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ){
	return NULL;
	}
	if( ( newpair->key = strdup( key ) ) == NULL ){
	return NULL;
	}
	if( ( newpair->value = strdup( value ) ) == NULL ){
	return NULL;
	}
	newpair->next = NULL;
	return newpair;
	}
//Insert a key-value pair into a hash table.
void ht_set( hashtable_t *hashtable, char *key, char *value ){
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;
	bin = ht_hash( hashtable, key );
	next = hashtable->table[ bin ];
	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ){
	last = next;
	next = next->next;
	}
//There's already a pair.  Let's replace that string.
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ){
	free( next->value );
	next->value = strdup( value );
// Nope, could't find it.  Time to grow a pair.
	} 
	else{
	newpair = ht_newpair( key, value );
// We're at the start of the linked list in this bin.
	if( next == hashtable->table[ bin ] ){
	newpair->next = next;
	hashtable->table[ bin ] = newpair;
//We're at the end of the linked list in this bin.
	} 
	else if ( next == NULL ){
	last->next = newpair;
//We're in the middle of the list.
	} 
	else{
	newpair->next = next;
	last->next = newpair;
	}
	}
	}
//Retrieve a key-value pair from a hash table.
	char *ht_get( hashtable_t *hashtable, char *key ){
	int bin = 0;
	entry_t *pair;
	bin = ht_hash( hashtable, key );
//Step through the bin, looking for our value.
	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ){
	pair = pair->next;
	}
//Did we actually find anything?
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ){
	return NULL;
	} 
	else{
	return pair->value;
	}
	}
//MAIN METHOD	
int main(){
	hashtable_t *hashtable = ht_create( 65536 );
	int i =0 ;
//H.A.S.H.T.A.B.L.E storing the entire data set.
	ht_set(hashtable, "hi", "Hello");
	ht_set(hashtable, "not feeling well", "Ok try to tell me what illness troubles you?");
	ht_set(hashtable, "fever",
						"Drink plenty of fluids. Fever can cause fluid loss and dehydration, so drink water, juices or broth.""\n"
						"For a child under age 1, use an oral rehydration solution such as Pedialyte.""\n"
						"These solutions contain water and salts proportioned to replenish fluids and electrolytes.""\n"
						"Pedialyte ice pops also are available.");
	ht_set(hashtable, "stomachache", 
						"Some studies suggest that mixing lime or lemon juice in water with a pinch of baking soda""\n" 
						"can help to relieve a variety of digestive complaints.""\n"
						"This mixture produces carbonic acid, which may help to reduce gas and indigestion.""\n"
						"It may also improve liver secretion and intestinal mobility.""\n" 
						"The acidity and other nutrients in lime or lemon juice can help to digest and absorb fats and alcohol""\n" 
						"while neutralizing bile acids and reducing acidity in the stomach.");
	ht_set(hashtable, "headache",
						"Sleep deprivation can be detrimental to your health in many ways,""\n" 
						"and may even cause headaches in some people.\n");
	ht_set(hashtable, "nausea",
						"A study of 2000 naval cadets found that those who were given one gram of ginger root suffered""\n" 
						"less seasickness and fewer cold sweats than the group given a placebo.""\n" 
						"It�s thought the active ingredients, gingerol and shogaol,""\n" 
						"inhibit the part of the brain that controls vomiting.""\n" 
						"To alleviate motion or morning sickness,""\n" 
						"naturopath Dr Soh�re Roked suggests chopping or grating 2cm of fresh ginger to use in cooking""\n" 
						"or made into tea.");
	ht_set(hashtable, "toothache",
						"Cloves contain a chemical compound that acts as an analgesic.""\n"
						"Either apply a clove directly to the sore area, or crush a clove up with water into a paste,""\n" 
						"then apply to the tooth.");
	ht_set(hashtable, "anxiety",
						"No need for beta �blockers� try a banana!""\n" 
						"Some musicians and actors swear that munching bananas before a performance can calm the nerves.""\n" 
						"Bananas are full of tryptophan, an amino acid that helps produce melatonin and serotonin,""\n" 
						"hormones that promote feelings of calmness.");
	ht_set(hashtable, "insomnia",
						"If the struggle to sleep is keeping you awake, try have some kiwis for supper.""\n"
						"Researchers found that people who ate two kiwis an hour before bedtime experienced""\n" 
						"better sleep quality and duration. It could be because the fruit has high levels of seratonin.""\n" 
						"Low levels of seratonin are associated with insomnia.""\n" 
						"Kiwis are also rich in folate � a deficiency of which can also cause sleep problems.""\n" 
						"A genius � and delicious � home remedy.");
	ht_set(hashtable, "energy",
						"You can find yerba mat� tea at most health stores or buy it online at yerbamatesouthafrica.com.""\n"
						"This herbal tea has a caffeine content roughly the same as coffee, giving you the same energy boost.""\n" 
						"It�s also rich in antioxidants � roughly 90% more than green tea.""\n" 
						"Also, its chemical compounds and nutrients affect your metabolism so that you get more energy""\n" 
						"from the food you eat.");
	ht_set(hashtable, "cholesterol",
						"Soluble fibre, like pectin found in pears, can reduce the absorption of LDL or �bad� cholesterol""\n" 
						"into your bloodstream. Pectin binds with cholesterol and helps carry it out of the body""\n" 
						"before it does you any damage.""\n" 
						"A pear contains about 3.5g of fibre and the recommended average daily intake is 18g.");
	ht_set(hashtable, "IBS",
						"Fennel contains a powerful essential oil called anethole.""\n" 
						"Anethole is an anti-inflammatory that reduces the amount of chemical signals released""\n" 
						"by some white blood cells that encourage localised inflammation.""\n" 
						"This fragrant oil is also responsible for fennel�s anti-spasmodic effect,""\n" 
						"which is why fennel seed tea is often taken to alleviate stomach cramps and period pain � ""\n"
						"making it one of the most versatile natural remedies");
	ht_set(hashtable, "constipation", 
						"Pure olive oil is more than just a healthy fat � its texture and consistency are a perfect""\n"
						"home remedy for constipation.""\n" 
						"Just take a tablespoon of olive oil and lemon juice in the morning before you eat anything else.""\n" 
						"It will stimulate your digestive system, which helps get things moving around your colon.""\n" 
						"Taken regularly, it can even prevent constipation.");
	ht_set(hashtable, "bloodpressure", 
						"If your numbers are a bit high, then beetroot might be your new best friend.""\n" 
						"It contains nitrate, which is converted into nitric acid when we eat it.""\n" 
						"This makes the muscular walls of the blood vessels relax and decrease blood pressure.""\n" 
						"Have it juiced, grated raw in a salad or roasted in chunks.""\n" 
						"Healthy eating doesn�t have to be boring!");
	ht_set(hashtable, "sinuses",
						"Horseradish contains a cocktail of chemicals that can thin mucus and help clear it from your sinuses.""\n" 
						"Grate fresh horseradish, or take a spoonful from a jar, and inhale it.""\n" 
						"If you�re really feeling brave, you can hold it in your mouth for a minute or two.");
	ht_set(hashtable, "pms",
						"Research shows that women who regularly eat foods high in thiamine (B1) riboflavin (B2) are""\n" 
						"less likely to get PMS. Lots of fortified cereals contain these B vitamins �""\n" 
						"but check the food label to make sure you don�t choose ones loaded with sugar.""\n" 
						"Eating breakfast and curing your ailments with natural remedies in one go? Winning!");
	ht_set(hashtable, "cramps",
						"Calcium can help reduce muscle cramping during menstruation.""\n" 
						"It�s available in supplement form and you can get hold of natural calcium from health shops.""\n" 
						"You can also add more calcium to your diet through natural foods: add sesame seeds to stir fries,""\n" 
						"or try frying almond flakes in olive oil and sprinkling on your salads.""\n" 
						"Dairy products and leafy green veg also contain high levels of calcium.");
	ht_set(hashtable, "heartburn",
						"Heartburn is the burning sensation in the upper chest we get after a rich meal,""\n" 
						"but instead of reaching for Gaviscon, try your spice rack.""\n" 
						"�The burning occurs when acid builds up,� says Dr Roked.""\n" 
						"�You can speed digestion by having a spoonful of turmeric in your food or after a meal,""\n" 
						"dissolved in hot water. It helps the gall bladder produce bile,""\n" 
						"which breaks the food down faster, so it doesn�t hang around long enough to cause heartburn.�");
	ht_set(hashtable, "joint",
						"Twisted your ankle trying carry two children at once? Try grinding chillies into a paste,""\n" 
						"then add them to a base cream or oil and apply to the affected area.""\n" 
						"The capsicum in chillies increases the pain-signalling chemical,""\n" 
						"then blocks its re-uptake by the nerve, stopping the pain signal to the brain.""\n" 
						"This is a really great emergency home remedy for treating sprains and muscle pain.");
	ht_set(hashtable, "blisters",
						"Whether you�ve singed your fingers on the oven or damaged your feet with your new party heels""\n" 
						"(worth it!), the aloe plant in your garden can help.""\n" 
						"After running the burn under cold water for 10 minutes,""\n" 
						"break off the tip of an aloe leaf and apply the oozing gel directly to the burn or blister.""\n" 
						"It�s also a great soothing remedy for sunburn.");
	ht_set(hashtable, "throat",
						"The antibacterial, astringent properties of sage will soothe the pain of a sore throat within two hours,""\n" 
						"says Dr Roked. To make a sage spray, take a handful of sage leaves,""\n" 
						"steep them in a teapot with boiling water and leave to cool.""\n" 
						"This liquid can then be sprayed on the back of your throat, or just drink it as a tea.");
	ht_set(hashtable, "backache",
						"This salad staple contains a compound, called 3-N-Butylphthalide in case you were wondering,""\n" 
						"which is a powerful painkiller. Author of Medicinal Cookery (Paperback Publishers)  Dale Pinnock,""\n" 
						"has found it useful in cases of arthritis, sprains and for people who experience ongoing pain.""\n" 
						"Eat it raw or juiced, but not cooked, as cooking breaks down the compound");
	ht_set(hashtable, "eczema",
						"Fill a muslin bag or nylon stocking with a handful of oats.""\n" 
						"Add the bag to your bath or use it as a soothing bath mitt.""\n" 
						"Oats contain anti-inflammatory compounds which help to soothe skin");
//H.A.S.H.T.A.B.L.E storing the entire data set.
	char ch;
    char str[100];
    int cnt = 0;
	char delim[] = " ";
	char *c[1000];
	char name[50];
		printf("HI I AM MEDBOT Ver1.3");printf("\n");printf("\n");
		printf("What is your name?");printf("\n");printf("\n");
		scanf("%s",&name);printf("\n");
	while(1){
	if(strcmp (str, "exit") == 0){	 
		exit(0);
	}
		printf("$(user_input): ");
		scanf (" %s", &str);
	int init_size = strlen(str);
	char *ptr = strtok(str, delim);
	while(ptr != NULL){
	c[i] = malloc(strlen(ptr) + 1);
	strcpy(c[i],ptr);
	i++;
	ptr = strtok(NULL, delim);
	}
	for(i = 0;i<sizeof(c) / sizeof(c[0]);i++){
	if(ht_get(hashtable, c[i])!=NULL){printf("\n");printf("\n");
		printf("$(chatbot_output):""\n");printf("\n");
		printf("Well");printf(" ");printf(name);printf(" ");printf("may i suggest!");printf("\n");printf("\n");
		printf(ht_get( hashtable, c[i] ) );printf("\n");printf("\n");
	break;
	}
	c[i]=0;
	break;
	printf("\n");
	}
	}
return 0;
}