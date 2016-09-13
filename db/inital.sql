PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE "products" (
    "id" TEXT NOT NULL,
    "name" TEXT NOT NULL,
    "price" INTEGER NOT NULL
);
INSERT INTO "products" VALUES('classic','Classic Ad',26999);
INSERT INTO "products" VALUES('standout','Standout Ad',32299);
INSERT INTO "products" VALUES('premium','Premium Ad',39499);
CREATE TABLE "matchingrules" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "match_key" TEXT NOT NULL,
    "match_value" TEXT NOT NULL
);
INSERT INTO "matchingrules" VALUES(1,'client','Unilever');
INSERT INTO "matchingrules" VALUES(2,'product','classic');
INSERT INTO "matchingrules" VALUES(3,'quantity','2');
INSERT INTO "matchingrules" VALUES(4,'client','Apple');
INSERT INTO "matchingrules" VALUES(5,'product','standout');
INSERT INTO "matchingrules" VALUES(6,'client','Nike');
INSERT INTO "matchingrules" VALUES(7,'product','premium');
INSERT INTO "matchingrules" VALUES(8,'quantity','4');
INSERT INTO "matchingrules" VALUES(9,'client','Ford');
INSERT INTO "matchingrules" VALUES(10,'quantity','3');
CREATE TABLE "actionrules" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "action_key" TEXT NOT NULL,
    "action_value" TEXT NOT NULL
);
INSERT INTO "actionrules" VALUES(1,'add_bonus','2');
INSERT INTO "actionrules" VALUES(2,'set_price','29999');
INSERT INTO "actionrules" VALUES(3,'set_price','37999');
INSERT INTO "actionrules" VALUES(4,'add_bonus','4');
INSERT INTO "actionrules" VALUES(5,'set_price','30999');
INSERT INTO "actionrules" VALUES(6,'set_price','38999');
CREATE TABLE "clients" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "name" TEXT NOT NULL
);
INSERT INTO "clients" VALUES(1,'Unilever');
INSERT INTO "clients" VALUES(2,'Apple');
INSERT INTO "clients" VALUES(3,'Nike');
INSERT INTO "clients" VALUES(4,'Ford');
CREATE TABLE "pricingrules" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "enabled" INTEGER NOT NULL,
    "name" TEXT NOT NULL
);
INSERT INTO "pricingrules" VALUES(1,1,'UNILEVER 3 FOR 2 CLASSIC');
INSERT INTO "pricingrules" VALUES(2,1,'APPLE  DISCOUNT STANDOUT');
INSERT INTO "pricingrules" VALUES(3,1,'NIKE DEAL FOR PREMIUM');
INSERT INTO "pricingrules" VALUES(4,1,'FORD 5 FOR 4 CLASSIC');
INSERT INTO "pricingrules" VALUES(5,1,'FORD DISCOUNT STANDOUT');
INSERT INTO "pricingrules" VALUES(6,1,'FORD DEAL FOR PREMIUM');
CREATE TABLE "pr2match" (
    "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "pr_id" INTEGER NOT NULL,
    "match_id" INTEGER NOT NULL
);
INSERT INTO "pr2match" VALUES(1,1,1);
INSERT INTO "pr2match" VALUES(2,1,2);
INSERT INTO "pr2match" VALUES(3,1,3);
INSERT INTO "pr2match" VALUES(4,2,4);
INSERT INTO "pr2match" VALUES(5,2,5);
INSERT INTO "pr2match" VALUES(6,3,6);
INSERT INTO "pr2match" VALUES(7,3,7);
INSERT INTO "pr2match" VALUES(8,3,8);
INSERT INTO "pr2match" VALUES(9,4,9);
INSERT INTO "pr2match" VALUES(10,4,2);
INSERT INTO "pr2match" VALUES(11,4,8);
INSERT INTO "pr2match" VALUES(12,5,9);
INSERT INTO "pr2match" VALUES(13,5,5);
INSERT INTO "pr2match" VALUES(14,6,9);
INSERT INTO "pr2match" VALUES(15,6,7);
INSERT INTO "pr2match" VALUES(16,6,10);
CREATE TABLE pr2action (
    "id" INTEGER NOT NULL,
    "pr_id" INTEGER NOT NULL,
    "action_id" INTEGER NOT NULL
);
INSERT INTO "pr2action" VALUES(1,'pr_id',1);
INSERT INTO "pr2action" VALUES(2,'pr_id',2);
INSERT INTO "pr2action" VALUES(3,'pr_id',3);
INSERT INTO "pr2action" VALUES(4,'pr_id',4);
INSERT INTO "pr2action" VALUES(5,'pr_id',5);
INSERT INTO "pr2action" VALUES(6,'pr_id',6);
INSERT INTO "pr2action" VALUES(1,1,1);
INSERT INTO "pr2action" VALUES(2,2,2);
INSERT INTO "pr2action" VALUES(3,3,3);
INSERT INTO "pr2action" VALUES(4,4,4);
INSERT INTO "pr2action" VALUES(5,5,5);
INSERT INTO "pr2action" VALUES(6,6,6);
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('clients',5);
INSERT INTO "sqlite_sequence" VALUES('matchingrules',10);
INSERT INTO "sqlite_sequence" VALUES('actionrules',6);
INSERT INTO "sqlite_sequence" VALUES('pricingrules',6);
INSERT INTO "sqlite_sequence" VALUES('pr2match',16);
CREATE UNIQUE INDEX "idx_product_id" on "products" (id ASC);
COMMIT;
