-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Дек 18 2018 г., 22:23
-- Версия сервера: 5.7.24-0ubuntu0.18.04.1
-- Версия PHP: 7.2.10-0ubuntu0.18.04.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `ClashOfMinds`
--

-- --------------------------------------------------------

--
-- Структура таблицы `games`
--

CREATE TABLE `games` (
  `game_id` int(11) NOT NULL,
  `ip` varchar(255) NOT NULL DEFAULT '0.0.0.0',
  `game_name` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `games`
--

INSERT INTO `games` (`game_id`, `ip`, `game_name`) VALUES
(12, '0.0.0.0', 'Game1');

-- --------------------------------------------------------

--
-- Структура таблицы `questions`
--

CREATE TABLE `questions` (
  `id` int(11) NOT NULL,
  `question` varchar(500) NOT NULL,
  `answer1` varchar(255) NOT NULL,
  `answer2` varchar(255) NOT NULL,
  `answer3` varchar(255) NOT NULL,
  `answer4` varchar(255) NOT NULL,
  `theme_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `questions`
--

INSERT INTO `questions` (`id`, `question`, `answer1`, `answer2`, `answer3`, `answer4`, `theme_id`) VALUES
(880, 'What is the location of London\'s National Gallery?', 'Trafalgar Square', 'Grosvenor Square', ' Leicester Square', 'Sloane Square', 1),
(881, 'What nationality was Edvard Munch, who produced the famous painting The Scream in 1893?', 'Norwegian', 'Swedish', 'German', 'Belgian', 1),
(882, 'Pablo Picasso was born in 1881 in which Spanish city?', 'Malaga', 'Madrid', 'Marbella', 'Murcia', 1),
(883, 'Which Dutch artist painted the Laughing Cavalier in 1624?', 'Frans Hals', 'Jan van der Meer', 'Ferdinand Bol', 'Johannes Vermeer', 1),
(884, 'Which English artist painted Rain, Steam and Speed - The Great Western Railway in 1844?', 'J M W Turner', 'Dante Gabriel Rossetti', 'John Constable', 'Ford Madox Brown', 1),
(885, 'What is the colloquial name for the 1871 painting Arrangement in Grey and Black: The Artist\'s Mother?', 'Whistler\'s Mother', 'Wilbur\'s Mother', 'Winslow\'s Mother', 'Winterton\'s Mother', 1),
(886, 'Between 1887 and 1888 Vincent van Gogh produced a series of still life paintings depicting which flowers?', 'Sunflowers', 'Daffodils', 'Geraniums', 'Tulips', 1),
(887, 'The English artist George Stubbs, who died in 1806, is best remembered for his paintings of what?', 'Horses', 'Dogs', 'Deer', 'Cats', 1),
(888, 'Who created the modern sculpture Angel of the North, that overlooks the A1 road and the East Coast main line in Gateshead?', 'Antony Gormley', 'Antony Greenly', 'Antony Gresley', 'Antony Grimley', 1),
(889, 'Hans Holbein the Younger was criticized by Henry VIII for painting a flattering portrait of whom?', 'Anne of Cleves', 'Anne Boleyn', 'Catherine Howard', 'Jane Seymour', 1),
(890, 'What is the approximate distance by road from Land\'s End to John O\'Groats?', '881 miles', '781 miles', '681 miles', '981 miles', 2),
(891, 'What name is given to the bay that lies to the West of Wales?', 'Cardigan Bay', 'Anglesey Bay', 'Carmarthen Bay', 'Irish Bay', 2),
(892, 'What is the name of the highest mountain in England?', 'Scafell Pike', 'Scafell', 'Helvellyn', 'Great Gable', 2),
(893, 'Approximately what percentage of people in the U.K. live in towns and cities?', '90', '80', '70', '60', 2),
(894, 'The Pennine Way connects which two places?', 'Edale and Kirk Yetholm', 'Macclesfield and Otterburn', 'Stafford and Durham', 'Ashbourne and Penrith', 2),
(895, 'Which island is the most southerly of the Channel Islands?', 'Jersey', 'Alderney', 'Guernsey', 'Sark', 2),
(896, 'Which town on Bideford Bay has a name the same as the title of a book by Charles Kingsley?', 'Westward Ho!', 'Westward ho', 'Westward Ho', 'Westward-Ho', 2),
(897, 'Which three counties adjoin Devon?', 'Cornwall, Somerset and Dorset', 'Cornwall, Dorset and Wiltshire', 'Cornwall, Somerset and Wiltshire', 'Somerset, Dorset and Wiltshire', 2),
(898, 'What is the largest town or city on the Isle of Man?', 'Douglas', 'Castletown', 'Peel', 'Ramsey', 2),
(899, 'Which forest can be found near the Southern border of Norfolk?', 'Thetford Forest', 'Swaffham Forest', 'Downham Forest', 'Dereham Forest', 2),
(900, 'In the UK, what are the two types of ISA?', 'Maxi and mini', 'Macro and micro', 'Little and large', 'Big and small', 3),
(901, 'Which Stock Exchange\'s activity is reflected by the Nikkei index?', 'Tokyo', 'Singapore', 'Manila', 'Hong Kong', 3),
(902, 'What sort of long-term loan is taken out to finance a house purchase?', 'Mortgage', 'Endowment', 'Debenture', 'Bridging Loan', 3),
(903, 'What is essential before obtaining an overdraft?', 'Valid bank account', 'Student union card', 'Credit card', 'Cheque book', 3),
(904, 'How are shareholders rewarded for their investment?', 'Dividend', 'Bonus', 'Interest-free loan', 'Salary', 3),
(905, 'What sort of loan relies purely upon the borrower\'s promise to repay it?', 'Unsecured', 'Soft', 'Flexible', 'Fixed', 3),
(906, 'How do lenders assess the level of risk attached to a borrower?', 'Credit score', 'Demographic group', 'Eye colour', 'Postcode', 3),
(907, 'What are \"Loan sharks\"?', ' Unlicensed lenders', 'Pawnbrokers', 'Fishmongers', 'Building societies', 3),
(908, 'What name is given to a mutual financial organisation run by its members?', 'Credit union', 'Debt union', 'Investment union', 'Trade union', 3),
(909, 'What type of overdraft has not been agreed in advance with the bank?', 'Unauthorised', 'Unsupported', 'Illicit', 'Illegal', 3),
(910, 'Which is the closest motorway to Legoland near Windsor?', 'M4', 'M1', 'M3', 'M40', 4),
(911, 'What is the price of an adult ticket for 1 day (£)?', '30', '25', '35', '40', 4),
(912, 'Miniland is constructed from the famous Lego bricks. How many bricks in Miniland?', '40 million', '10 million', '20 million', '30 million', 4),
(913, '\"Spellbreaker 4D\" opened in 2006 - what is it?', 'A 3D theatre', 'A live action show', 'A roller coaster ride', 'A film all about Legoland', 4),
(914, 'What is the \"Digger Challenge\"?', 'An opportunity to drive a digger', 'A digger assembly line', 'A digger demonstration', 'An exhibition of diggers', 4),
(915, 'Which of these real life stunts is NOT featured in the 2006 brand new action show?', 'Dangerous underwater rescues', 'Daring high dives', 'Exciting jet-ski races', 'Fast-paced action sequences', 4),
(916, 'At how many places in the park can you buy food and drink?', '13', '11', '15', '17', 4),
(917, 'What unusual animal can you find in Waterworks?', 'A talking rhino', 'A dancing bear', 'A singing hippo', 'A water-skiing elephant', 4),
(918, 'Where are you welcome to picnic?', 'The enchanted forest', 'The dancing meadow', 'The magic field', 'The squirrel wood', 4),
(919, 'How many different mazes are there to get lost in?', '3', '1', '2', '4', 4),
(920, 'Which EastEnders character announced on Friday that she wants a baby?', 'Jane Beale', 'Janine Butcher', 'Sam Mitchell', 'Stacey Slater', 5),
(921, 'Which footballer announced last week that he and his brother could win X Factor?', 'Carlos Tevez', 'Theo Walcott', 'Heurelho Gomes', 'Joey Barton', 5),
(922, 'Who plays astronaut Lieutenant Payton in the science fiction film Pandorum due for UK release this week?', 'Dennis Quaid', 'Kevin Costner', 'Kevin Spacey', 'Bruce Willis', 5),
(923, 'Which Australian pop duo today rereleased in the UK their 2005 debut single 4ever?', 'The Veronicas', 'The Victorias', 'The Vanessas', 'The Valeries', 5),
(924, 'Which comedian presented Saturday\'s Radio 2 music documentary British Steel: How Heavy Metal Conquered The World?', 'Justin Lee Collins', 'Jack Dee', 'Tim Vine', 'Paul Whitehouse', 5),
(925, 'Which former England cricketer appeared on Strictly Come Dancing at the weekend?', 'Phil Tufnell', 'Mike Gatting', 'Geoffrey Boycott', 'Ian Botham', 5),
(926, 'An episode of The Simpsons screened last week revealed that Jeff Albertson is the real name of which character?', 'Comic Book Guy', 'Disco Stu', 'Duffman', 'Krusty the Clown', 5),
(927, 'What is the title of Justin Moore\'s single that became the US No 1 in the country music charts last week?', 'Small Town USA', 'Hick Town USA', 'Frontier Town USA', 'Big Town USA', 5),
(928, 'What is the title of the new Michael Moore documentary film due for release this week?', 'Capitalism: A True Story', 'Communism: A True Story', 'Conservatism: A True Story', 'Fascism: A True Story', 5),
(929, 'What is the subject of the film released yesterday titled: Morris: A Life With Bells On?', 'Morris dancing', 'Bell ringing', 'Morris cars', 'Nine Men\'s Morris', 5),
(930, 'Which alcohol is traditionally added to the base of a Christmas trifle?', 'Sherry', 'Gin', 'Vodka', 'Whisky', 6),
(931, 'Stollen is a traditional Christmas fruit loaf of which country?', 'Germany', 'France', 'Greece', 'Italy', 6),
(932, 'What is the meal consisting of left-over vegetables served on 26th December?', 'Bubble And Squeak', 'Champ', 'Frittata', 'Rösti', 6),
(933, 'What is the Christmas treat \"panettone\"?', 'Italian fruitbread', 'Scottish cake made with mincemeat', 'French spicy dessert', 'Austrian winter cheesecake', 6),
(934, 'What would you find under the icing of a Christmas Cake?', 'Marzipan', 'Pastry', 'Jam', 'Buttercream', 6),
(935, 'What in Britain was traditionally mixed into a Christmas pudding \"for good luck\"?', 'Coin', 'Horseshoe', 'Key', 'Ring', 6),
(936, 'Traditionally served hot at Christmas, with what is mulled wine concocted?', 'Red wine, sugar, spices', 'Red wine, cranberry juice, orange', 'Red wine, lemonade', 'White wine, assorted fruits', 6),
(937, 'A traditional luxury Christmas starter, what is gravadlax?', 'Cured salmon', 'Mackerel pâté', 'Smoked trout', 'Soused herring', 6),
(938, 'What sauce is traditionally served at Christmas with turkey?', 'Cranberry', 'Cheese', 'Apple', 'Tomato', 6),
(939, 'Which traditional Christmas treat is also used in Cockney rhyming slang?', 'Mince pies', 'Figgy pudding', 'Chocolate logs', 'Brandy butter', 6),
(940, 'Orecchietta is pasta in what sort of shapes?', 'Ears', 'Parcels', 'Spirals', 'Tubes', 7),
(941, 'Which meat is traditionally seasoned with rosemary?', 'Lamb', 'Beef', 'Pork', 'Turkey', 7),
(942, 'Around which river is Port wine traditionally produced?', 'Douro', 'Ebro', 'Garonne', 'Tagus', 7),
(943, 'What is chorizo?', 'Spanish Sausage', 'Mexican Chicken', 'Italian Cheese', 'Greek Dessert', 7),
(944, 'What is the traditional topping on a Lancashire Hotpot?', 'Sliced Potato', 'Mashed Potato', 'Dumplings', 'Breadcrumbs', 7),
(945, 'What is another name for Okra?', 'Ladies\' Fingers', 'Pirate\'s Fingers', 'Dead Man\'s Fingers', 'Blacksmith\'s Fingers', 7),
(946, 'What is Wasabi?', 'Japanese Horseradish', 'Hawaiian Fruit', 'Chinese Mushroom', 'Brazilian Root Vegetable', 7),
(947, 'By what name do we normally refer to the Chinese Gooseberry?', 'Kiwi Fruit', 'Mango', 'Passion Fruit', 'Star Fruit', 7),
(948, 'From what fruit is Calvados distilled?', 'Apples', 'Grapes', 'Peaches', 'Pears', 7),
(949, 'From what is Welsh Laverbread made?', 'Seaweed', 'Leeks', 'Lettuce', 'Spinach', 7),
(950, 'Who was the first presenter of \"A Question of Sport\"?', ' Stuart Hall', 'Sue Barker', 'David Vine', 'David Coleman', 8),
(951, 'What is the state in the New England region of the northeastern United States?', 'Massachusetts', 'Massachusets', 'Masachewsetts', 'Masserchusetts', 8),
(952, 'Which Italian city is Mount Vesuvius closest to?', 'Naples', 'Milan', 'Turin', 'Rome', 8),
(953, 'Which film won the 81st Academy Award for Best Picture of 2008 on February 22, 2009?', 'Slumdog Millionaire', 'Frost/Nixon', 'The Curious Case of Benjamin Button', 'The Reader', 8),
(954, 'In which year did the character \"Batman\" first appear in Detective Comics number 27?', '1939', '1929', '1949', '1959', 8),
(955, 'Samsung Electronics is a company from which country?', 'South Korea', 'Japan', 'China', 'Indonesia', 8),
(956, 'What nationality was the artist Herge, who created \"The Adventures of Tintin\" series of comic books?', 'Belgian', 'Dutch', 'French', 'German', 8),
(957, 'Who played the female lead in the 1989 film \"Driving Miss Daisy\"?', 'Jessica Tandy', 'Jessica Curry', 'Jessica Dixon', 'Jessica Maplin', 8),
(958, 'Who is the first and only Catholic president of the United States?', 'John F Kennedy', 'Dwight D Eisenhower', 'Lyndon B Johnson', 'Richard Nixon', 8),
(959, 'Which team has played in the top division of English football since 1938 with the exception of the 1974-75 season?', 'Manchester United', 'Liverpool', 'Evertor', 'Arsenal', 8),
(960, 'Who was the founder of the Scout Movement?', 'Robert Baden-Powell', 'H G Wells', 'Sigmund Freud', 'Winston Churchill', 8),
(961, 'The Lockheed Martin F-16 jet is known as the what?', 'Fighting Falcon', 'Ferocious Feline', 'Fast Freddie', 'Freedom Fighter', 8),
(962, 'Who is the King of the Gods in Greek Mythology?', 'Zeus', 'Apollo', 'Dionysus', 'Poseidon', 8),
(963, 'A squirrel\'s nest is called a what?', 'Drey', 'Form', 'Seth', 'Eyrie', 8),
(964, 'Who betrayed Samson to the Philistines?', 'Delilah', 'Diamante', 'Daphne', 'Dorian', 8),
(965, 'What is Harry\'s surname in the \"Dirty Harry\" film series?', 'Callahan', 'Carnegie', 'Colt', 'Crown', 8),
(966, 'David Howell Evans is more widely known by which stage name?', 'The Edge', 'The Line', 'The Cliff', 'The Wall', 8),
(967, 'Who was the star of the 1970s sitcom \"Up Pompeii!\"?', 'Frankie Howerd', 'Harry H Corbett', 'Kenneth Williams', 'Sid James', 8),
(968, 'Sports car manufacturer Ferrari are based where?', 'Maranello, Italy', 'Montevideo, Uruguay', ' Malmo, Sweden', 'Madrid, Spain', 8),
(969, 'According to the 2009 CIA World Factbook, which country has the longest life expectancy?', 'Macau', 'Japan', 'Singapore', 'Andorra', 8),
(970, 'Which 1957 Treaty created the European Economic Community?', 'Rome', 'Paris', 'Madrid', 'Brussels', 8),
(971, 'Who shot and killed Lee Harvey Oswald?', 'Jack Ruby', 'Jack Opal', 'Jack Jade', 'Jack Diamond', 8),
(972, 'What is the fictional seaside resort where the BBCs \"Dad\'s Army\" was set?', 'Walmington-on-Sea', 'Walmington-on-Sea', 'Royston Vasey', 'Crinkley Bottom', 8),
(973, 'Which Embassy was the scene of the 1980 Special Air Service raid in South Kensington, London?', 'Iranian', 'Iraqi', 'French', 'Jordanian', 8),
(974, 'Which author wrote \"Brave New World\"?', 'Aldous Huxley', 'D H Lawrence', 'Graham Greene', 'Thomas Hardy', 8),
(975, 'Who composed \"The Nutcracker\"?', 'Tchaikovsky', 'Mozart', 'Handel', 'Beethoven', 8),
(976, 'Which dinosaur\'s name means \"roof lizard\"?', 'Stegosaurus', 'Triceratops', 'Tyrannosaurus', 'Pteradactyl', 8),
(977, 'Which football club moved to Milton Keynes to eventually form \"MK Dons\"?', 'Wimbledon FC', 'Telford United FC', 'St Leonards FC', 'Gloucester United FC', 8),
(978, 'Which lager is \"Probably the best lager in the world\"?', 'Carlsberg', 'Carling', 'Grolsch', 'Stella Artois', 8),
(979, 'Blue Mountain Coffee comes from where?', 'Jamaica', 'Kenya', 'Colombia', 'Costa Rica', 8),
(980, 'How long does it take for the Earth to complete an orbit of the Sun?', 'Approximately 365 days', 'Approximately 30.5 days', 'Approximately 28 days', 'Approximately 7 days', 9),
(981, 'Approximately how fast does the fastest raindrop fall?', '10 m/s', '1 m/s', '20 m/s', '5 m/s', 9),
(1421, 'Pepakura is the art of making 3D models from what?', 'Paper', 'Clay', 'Matchsticks', 'Plasticine', 10),
(1422, 'What was the first name of Mr Hornby, inventor of Meccano?', 'Frank', 'Fred', 'Ford', 'Felix', 10),
(1423, 'When Tri-Ang Railways introduced their locomotive 46201 in 1950, what name did it carry?', 'Princess Elizabeth', 'Princess Beatrice', 'Princess Louise', 'Princess Victoria', 10),
(1424, 'Peyote stitch is a technique used in what?', 'Beadwork', 'Crocheting', 'Embroidery', 'Knitting', 10),
(1425, 'What is the name of the folk art of decorative painting on tin and wooden utensils and furniture?', 'Tole painting', 'Mole painting', 'Bole painting', 'Dole painting', 10),
(1426, 'Beamish Museum in County Durham houses a collection of over 400 hooky and proggy what?', 'Mats', 'Quilts', 'Gloves', 'Blankets', 10),
(1427, 'To a metalworker, what can be diamond, needle or riffler?', 'Files', 'Drills', 'Lathes', 'Welding joints', 10),
(1428, 'To a woodworker, what can be bullnose, chariot or thumb?', 'Planes', 'Saws', 'Screws', 'Nails', 10),
(1429, 'What is the literal translation of the word \"calligraphy\"?', 'Beautiful writing', 'Colourful writing', 'Joyful writing', 'Wonderful writing', 10),
(1430, 'What is of primary concern to a fishkeeper?', 'The nitrogen cycle', 'The oxygen cycle', 'The hydrogen cycle', 'The halogen cycle', 10),
(1431, 'Which is the nearest city to the resort of Portobello?', ' Edinburgh', 'Brighton', 'Liverpool', 'Portsmouth', 11),
(1432, 'Former prime minister Edward Heath regularly conducted the annual carol service in which Kent resort?', 'Broadstairs', 'Herne Bay', 'Margate', 'Ramsgate', 11),
(1433, 'The Northern Ireland Prison Service College is situated on the outskirts of which resort?', 'Millisle', 'Newcastle', 'Portrush', 'Portstewart', 11),
(1434, 'Which Isle of Man resort hosts the annual World Tin Bath Championship?', 'Castletown', 'Douglas', 'Port Erin', 'Ramsey', 11),
(1435, 'A plaque is set into the Blackpool tram lines commemorating the death of which Coronation Street character in 1989?', 'Alan Bradley', ' Len Fairclough', 'Ernest Bishop', 'Jerry Booth', 11),
(1436, 'Which Yorkshire resort lies just south of Flamborough Head?', 'Bridlington', 'Robin Hood\'s Bay', 'Scarborough', 'Whitby', 11),
(1437, 'In which Welsh resort is Coney Beach Pleasure Park, modelled on Coney Island, New York?', 'Porthcawl', 'Llandudno', 'Rhyl', 'Tenby', 11),
(1438, 'A narrow-gauge railway ran from 1879 until 1929 between Halesworth and which Suffolk resort?', 'Southwold', 'Orford', 'Lowestoft', 'Aldeburgh', 11),
(1439, 'The world\'s first mountain-climbing cog railway reached which New Hampshire summit in 1869?', 'Mount Washington', 'Mount Lincoln', 'Mount Jefferson', 'Mount Adams', 12),
(1440, 'Which year saw the opening of San Francisco\'s first cable-operated street railway?', '1873', '1883', '1893', '1903', 12),
(1441, 'In 1971 the reconstruction of London Bridge was completed at which Arizona location?', 'Lake Havasu City', 'Lake Havapu City', 'Lake Havago City', 'Lake Havado City', 12),
(1442, 'In which state is the Little Bighorn Battlefield National Monument, site of the 1876 battle?', 'Montana', 'Colorado', 'Utah', 'Wyoming', 12),
(1443, 'Santa Catalina Island is a popular tourist destination lying off the coast of which state?', 'California', 'Florida', 'Massachusetts', 'Texas', 12),
(1444, 'The beach resort of Coney Island is in which New York borough?', 'Brooklyn', 'The Bronx', 'Queens', 'Staten Island', 12),
(1445, 'The Hormel Foods Corporation runs a museum in Austin, Minnesota, dedicated to which product?', 'Spam', 'Kool-Aid', 'Jell-O', 'Golden Grahams', 12),
(1446, 'Which river flows through the Grand Canyon?', 'Colorado', 'Columbia', 'Cumberland', 'Cheyenne', 12),
(1447, 'In which state is the Mount Rushmore National Memorial?', 'South Dakota', 'Wisconsin', 'Minnesota', 'North Dakota', 12),
(1448, 'What is the name of the famous geyser in Yellowstone National Park?', 'Old Faithful', 'Old Ironsides', 'Old Smoky', 'Old Timer', 12),
(1449, 'What is the full name of the country known as the UAE?', 'United Arab Emirates', 'Union of Arabian Emirates', 'Union of Arab Emirates', 'United Arabian Emirates', 13),
(1450, 'What is included in a BLT sandwich?', 'Bacon, lettuce and tomato', 'Beef, lettuce and tomato', 'Bacon, lard and tripe', 'Beef, lime and turnip', 13),
(1451, 'For what is the clothing size XL an abbreviation?', 'Extra Large', 'Extra Light', 'Extra Lined', 'Extra Loose', 13),
(1452, 'By what initials was President Kennedy of the USA known?', 'JFK', 'JK', 'BBK', 'RFK', 13),
(1453, 'Which abbreviation is associated with Colonel Sanders?', 'KFC', 'LBW', 'WBA', 'ARP', 13),
(1454, 'What nationality is the car manufacturer BMW?', 'German', 'American', 'British', 'Swedish', 13),
(1455, 'In cricket what is an ODI?', 'One Day International', 'Over Delivered Illegally', 'One Day Innings', 'Off Drive Initiative', 13),
(1456, 'Which British political party did David Owen and Shirley Williams help to create?', 'SDP', 'SDLP', 'SNP', 'UKIP', 13),
(1457, 'Which British nationalised industry was known as the NCB?', 'National Coal Board', 'National Car Builders', 'National Computer Business', 'National Credit Bank', 13),
(1458, 'Which organisation, known by its initials, is the UK\'s leading drama school?', 'RADA', 'LIPA', 'RSC', 'EQUITY', 13),
(1459, 'OPEC stands for the Organization of Petrol Exporting what?', 'Countries', 'Corporations', 'Companies', 'Confederations', 14),
(1460, 'Established in 1904 by Sir Herbert Beerbohm Tree, RADA is the Royal Academy of Dramatic what?', 'Art', 'Artists', 'Actresses', 'Actors', 14),
(1461, 'At the 2006 football World Cup, what connection did the WAGs have to the England team?', 'Wives and girlfriends', 'Wingers and goalkeepers', 'Waiters and gophers', 'Writers and groupies', 14),
(1462, 'The acronym WASP, meaning a White Anglo-Saxon Protestant, originated in which country?', 'United States', 'South Africa', 'New Zealand', 'Canada', 14),
(1463, 'The Swedish pop group ABBA chose their name from the initial letters of their what?', 'First names', 'Favourite musical keys', 'Home towns', 'Surnames', 14),
(1464, 'In the 1964 film Carry On Spying, what was the name of the sinister organisation, a parody of SMERSH in the James Bond novels?', 'STENCH', 'SMUDGE', 'SLUDGE', 'STODGE', 14),
(1465, 'What type of weapon is a SAM?', 'Surface-to-air missile', 'Submarine attack missile', 'Strategically-armed missile', 'Strategically-aimed missile', 14),
(1466, 'In the early days of science fiction, what was a BEM?', 'Bug-eyed monster', 'Biologically engineered mortal', 'Big evil Martian', 'Bad extraterrestrial mutant', 14),
(1467, 'The consumer group CAMRA is the Campaign for Real what?', 'Ale', 'Acronyms', 'Aubergines', 'Artichokes', 14),
(1468, 'UMIST is the University of Manchester Institute of what?', 'Science and Technology', 'Sociology and Teaching', 'Space and Telescopes', 'Submarines and Torpedoes', 14),
(1469, 'Who assassinated Abraham Lincoln in 1865?', 'John Wilkes Booth', 'John Wilkinson Booth', 'John Wilson Booth', 'John Wilton Booth', 15),
(1470, 'Which conflict was triggered by the assassination of Archduke Franz Ferdinand of Austria?', 'World War One', 'The Crimean War', 'The Spanish Civil War', 'The Boer War', 15),
(1471, 'In which city was John F Kennedy assassinated in 1963?', 'Dallas', 'Denver', 'New York', 'Washington DC', 15),
(1472, 'Which Russian politician was assassinated by Ramon Mercader in 1940?', 'Leon Trotsky', 'Joseph Stalin', 'Vladimir Lenin', 'Nikolai Bhukarin', 15),
(1473, 'The Bulgarian journalist Georgi Markov was assassinated in London in 1978 by a poisoned what?', 'Umbrella', 'Pen', 'Sausage roll', ' Doughnut', 15),
(1474, 'Which Roman emperor was assassinated on 15 March, 44 BC?', 'Julius Caesar', 'Nero', 'Tiberius', 'Caligula', 15),
(1475, 'The Prime Minister of which country was assassinated in 1986?', 'Sweden', 'Norway', 'Finland', 'Denmark', 15),
(1476, 'In which English cathedral was Thomas Beckett assassinated in 1170?', 'Canterbury', 'Durham', 'Salisbury', 'Winchester', 15),
(1477, 'Ross McWhirter, who was assassinated by the IRA in 1975, was co-author of which reference book?', 'Guinness Book of Records', 'Encyclopaedia Britannica', 'Oxford English Dictionary', 'Who\'s Who', 15),
(1478, 'In which country was Mahatma Gandhi assassinated in 1948?', 'India', 'Iraq', 'Iran', 'Egypt', 15),
(1479, 'An average family car in the UK is required to take its MOT test on reaching what age?', 'Three years', 'Two years', 'Four years', 'Five years', 16),
(1480, 'First introduced as an emergency measure in 1965, what became the upper speed limit on UK motorways in 1967?', '70 mph', '65 mph', '75 mph', '80 mph', 16),
(1481, 'In which British city are the headquarters of the Driver and Vehicle Licensing Agency?', 'Swansea', 'Edinburgh', 'Cardiff', 'Belfast', 16),
(1482, 'What colour is the background of directional signs to tourist attractions in the UK?', 'Brown', 'Blue', 'White', 'Yellow', 16),
(1483, 'Warning signs on British roads are normally what shape?', 'Triangular', 'Rectangular', 'Haxagonal', 'Square', 16),
(1484, 'What is the official road safety manual for the UK?', 'The Highway Code', 'The Road Code', 'The Traffic Code', 'The Green Cross Code', 16),
(1485, 'What is the name for the agreement between insurance companies by which each insurer pays for repairs to its own policyholder\'s vehicle?', 'Knock for knock', 'Hit for hit', 'Dent for dent', 'Tit for tat', 16),
(1486, 'What animal appears on UK traffic signs giving tourist directions to a zoo?', 'Elephant', 'Camel', 'Gorilla', 'Giraffe', 16),
(1487, 'How far apart are the \"countdown\" markers before motorway exits?', '100 yards', '200 yards', '150 yards', '50 yards', 16),
(1488, 'What type of car tyre, now almost universal, was developed by the Michelin company in 1946?', 'Radial', 'Radian', 'Radical', 'Randome', 16),
(1489, 'What is the family name of the Duke Of Edinburgh?', 'Mountbatten', 'Papadopoulos', 'McBatten', 'Windsor', 17),
(1490, 'Who is the father of Princess Beatrice?', 'Prince Andrew', 'Prince Charles', 'Prince Edward', 'Prince Philip', 17),
(1491, 'In which year was Queen Elizabeth II born?', '1926', '1922', '1924', '1928', 17),
(1492, 'Where did Prince Charles\' investiture as Prince Of Wales take place?', 'Caernarfon', 'Caerphilly', 'Caersws', 'Carmarthen', 17),
(1493, 'What was the name of Queen Elizabeth II\'s sister?', 'Margaret', 'Mary', 'Sarah', 'Alexandra', 17),
(1494, 'In which year was Prince William born?', '1982', '1978', '1985', '1987', 17),
(1495, 'How many older brothers does Prince Edward have?', '2', '1', '3', '4', 17),
(1496, 'What is the name of the Royal residence in Norfolk?', 'Sandringham', 'Holyrood', 'Gatcombe', 'Balmoral', 17),
(1497, 'Who is third in line to the British throne?', 'Prince Harry', 'Prince Andrew', 'Prince William', 'Princess Anne', 17),
(1498, 'In which year did Elizabeth the Queen Mother die?', '2002', '1999', '1997', '2005', 17),
(1499, 'Which manufacturer introduced the Accord model in 1976?', 'Honda', 'Mitsubishi', 'Nissan', 'Toyota', 18),
(1500, 'Which Ford model was introduced in 1982 as a replacement for the Cortina?', 'Sierra', 'Fiesta', 'Siesta', 'Taurus', 18),
(1501, 'Which British manufacturer introduced the Cresta model in 1954?', 'Vauxhall', 'Rover', 'Morris', 'Ford', 18),
(1502, 'What did the letters MG originally stand for in the name of the car company?', 'Morris Garages', 'Midland Garages', 'Merseyside Garages', 'Manchester Garages', 18),
(1503, 'In which city is the car factory known as the Longbridge plant?', 'Birmingham', 'Liverpool', 'London', 'Nottingham', 18),
(1504, 'In 1905 Vauxhall Motors opened the UK\'s largest car plant in which town?', 'Luton', 'Hemel Hempstead', 'Dunstable', 'Bedford', 18),
(1505, 'What make of car is Herbie, who made his film debut in 1969?', 'Volkswagen', 'Opel', 'Audi', 'BMW', 18),
(1506, 'The manufacturer Fiat is based in which Italian city?', 'Turin', 'Naples', 'Milan', 'Bologna', 18),
(1507, 'Nicole and Papa were characters in a famous series of 1990s TV ads for which manufacturer?', 'Renault', 'Volvo', 'Peugeot', 'Citroen', 18),
(1508, 'What is the name of the Jeep model first produced in 1974?', 'Cherokee', 'Chippewa', 'Choctaw', 'Commanche', 18),
(1509, 'Which is not a London Underground stop - Angel, Bank, Palace, Temple?', 'Palace', 'Bank', 'Angel', 'Temple', 19),
(1510, 'Which countries co-operated to produce Concorde supersonic aircraft?', 'Britain and France', 'Britain and the USA', 'France and Germany', 'France and the USA', 19),
(1511, 'Which mode of transport did Christopher Cockerell develop in the 1950s?', 'Hovercraft', 'Hot Air Balloon', 'Roller Skates', 'Space Shuttle', 19),
(1512, 'Which vehicles can have two-stroke or four-stroke engines?', 'Motor Cycles', 'Dragsters', 'Steamrollers', 'Trams', 19),
(1513, 'What type of vessel was the SS Great Britain?', 'Steamship', 'Galleon', 'Car Ferry', 'Submarine', 19),
(1514, 'Which English town is closest to the Channel Tunnel entrance?', 'Folkestone', 'Frome', 'Falmouth', 'Felixstowe', 19),
(1515, 'Which city is at the northern end of the A1 road in the UK?', 'Edinburgh', 'Sheffield', 'Durham', 'Aberdeen', 19),
(1516, 'Where do Shinkansen \"bullet trains\" operate?', 'Japan', 'Thailand', 'Malaysia', 'Korea', 19),
(1517, 'How wide is \"standard gauge\" railway, used in 60% of the world\'s railways?', '4 feet 8.5 inches', '5 feet 2.5 inches', '5 feet 7.5 inches', '6 feet 1.5 inches', 19),
(1518, 'Who introduced the first motor truck in 1896?', 'Daimler', 'Lada', 'Nissan', 'Skoda', 19),
(1519, 'What was the name of the world\'s first public railway, opened in 1825?', 'Stockton and Darlington', 'Stockton and Durham', 'Stockton and Hartlepool', 'Stockton and Middlesbrough', 20),
(1520, 'Which London terminal station was opened in 1854 as the headquarters of the Great Western Railway?', 'Paddington', 'Waterloo', 'Kings Cross', 'Euston', 20),
(1521, 'Which line of the London Underground is coloured yellow on the map?', 'Circle Line', 'Central Line', 'District Line', 'Northern Line', 20),
(1522, 'Which British city is served by Temple Meads station?', 'Bristol', 'Birmingham', 'Cardiff', 'Edinburgh', 20),
(1523, 'In what year were the railways nationalised to form British Railways?', '1948', '1938', '1928', '1958', 20),
(1524, 'Where is the National Railway Museum situated?', 'York', 'Swindon', 'Crewe', 'Doncaster', 20),
(1525, 'Between 1929 and 1972 the Golden Arrow was a prestigious train that ran between London and which other capital city?', 'Paris', 'Cardiff', 'Edinburgh', 'Brussels', 20),
(1526, 'When the Trans-Siberian Railway opened in 1916, in which city was its western terminus?', 'Moscow', 'Omsk', 'St Petersburg', 'Vladivostok', 20),
(1527, 'Which British city opened an underground railway system in 1896?', 'Glasgow', 'Liverpool', 'Edinburgh', 'Manchester', 20),
(1528, 'Eurostar services to Paris and Brussels began in 1994 from which London terminal station?', 'Waterloo', 'Paddington', 'St Pancras', 'Victoria', 20);

-- --------------------------------------------------------

--
-- Структура таблицы `Themes`
--

CREATE TABLE `Themes` (
  `Theme_ID` mediumint(9) NOT NULL,
  `Theme` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `score` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `users`
--

INSERT INTO `users` (`id`, `name`, `password`, `score`) VALUES
(9, 'Irooooda', '123123', 2),
(10, '123', '123', 141),
(11, 'Doston', 'dostonlox', 0),
(13, 'Dostonpalox', 'dostonlox', 5);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `games`
--
ALTER TABLE `games`
  ADD PRIMARY KEY (`game_id`),
  ADD UNIQUE KEY `game_name` (`game_name`);

--
-- Индексы таблицы `questions`
--
ALTER TABLE `questions`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `Themes`
--
ALTER TABLE `Themes`
  ADD PRIMARY KEY (`Theme_ID`);

--
-- Индексы таблицы `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `name` (`name`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `games`
--
ALTER TABLE `games`
  MODIFY `game_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;
--
-- AUTO_INCREMENT для таблицы `questions`
--
ALTER TABLE `questions`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1529;
--
-- AUTO_INCREMENT для таблицы `Themes`
--
ALTER TABLE `Themes`
  MODIFY `Theme_ID` mediumint(9) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
