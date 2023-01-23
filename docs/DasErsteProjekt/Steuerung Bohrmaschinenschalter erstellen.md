**Neue Steuerung erstellen Bohrmaschinenschalter. (Ein- Ausschalter an Ständerbohrmaschine)**

(Mit einem Knopf wird ein Ausgang an geschalten, mit einem anderen Knopf wird ein Ausgang aus geschalten) 

**Type Libary auf der rechten Seite ist Schreibgeschützt, deshalb sollte diese anstatt der linken verwendet werden.**

1.  Mapping in Baum links mit Doppelklick wählen.

![](https://user-images.githubusercontent.com/113907476/212993771-b36281c6-3c24-4fd9-8d51-cd1b5beb4657.png)

2\. Type Libary öffnen. Ordner io öffnen. Ordner Hutschienenmoped öffnen. Baustein "Hutschienenmoped\_4\_DO" mit Maus in Arbeitsfenster ziehen.

{Hutschienenmoped mit 4 Ausgängen DigitalOutput Q1 - Q4 (Lampen)} 

\-> Baustein wird eingefügt.

![](https://user-images.githubusercontent.com/113907476/212994540-408bd26f-c121-47f9-9a93-c759b5c3d136.png)

3\. Type Libary öffnen. Ordner io öffnen. Ordner Hutschienenmoped öffnen. Baustein "Hutschienenmoped\_3\_DI\_SINGLE\_CLICK" mit Maus in Arbeitsfenster ziehen (zusätzlich)

(Schalter mit 3 Eingängen DigitalInput I1 - I3 {SingleClick Schalter blau, rot und Atom}

![](https://user-images.githubusercontent.com/113907476/212996213-bcef4c26-da89-40f5-822a-6044431a62a9.png)

4\. Damit die Bausteine nach dem Start funktionieren muss jeweils QI auf TRUE gesetzt werden.

Doppelklick auf FALSE und TRUE eingeben.

![](https://user-images.githubusercontent.com/113907476/212996770-5998ec9b-9c62-45c9-a37d-fdf9f7a4b88a.png)

5\. Damit die Ein- und Ausgänge funktionieren, müssen die grau hinterlegten Bezeichnungen angeklickt (Doppelklick) und mit Enter bestätigt werden.

\-> Die Schriftfarbe ändert sich dann zu schwarz.

![](https://user-images.githubusercontent.com/113907476/212997168-851d2855-f796-40fd-8fa6-a185e7011506.png)

6\. Die Bausteine können zu einer Gruppe zusammengefüg werden.

Dazu mit gedrückter linker Maustaste ein Fenster über die Bausteine aufziehen und loslassen. Beide Bausteine werden blau. Rechten Mausklick auf einen der gewählten Bausteine.

\-> Fenster öffnet. New Group wählen. -> Bausteine werden zu einer Gruppe zusammengefügt.

![](https://user-images.githubusercontent.com/113907476/212998191-7a982154-1dcb-4c5b-bd9a-8c1d5d86f877.png)

7\. Gruppennamen vergeben (mapping) und Gruppenbeschreibung bei Comment eingeben (mapping der Ein- und Ausgänge....)

![](https://user-images.githubusercontent.com/113907476/212998790-97736f43-4fba-4b4c-a56d-4d57073a924f.png)

8\. Gruppe anwählen -> wird blau. Rechtsklick -> Fenster öffnet. Convert Group to Subapp wählen.

![](https://user-images.githubusercontent.com/113907476/212999266-82fa444e-821e-44b4-bae1-4f58f9ff76ac.png)

\-> Untere Leiste bei Properties ändert sich.

![](https://user-images.githubusercontent.com/113907476/212999686-ad88ad9e-42da-4110-b7d4-c7f5e684c6d1.png)

9\. Properties anwählen. Edit Events anwählen. Rechts daneben in Leiste öffnen sich Inputs und Outputs mit einem grünen Plus daneben.

\+ auf der Seite Inputs drücken 1x.

\-> Ein neuer Input EI1 wird in der Subapp hinzugefügt. Sichtbar in Tabelle und oben links in der Gruppe.

![](https://user-images.githubusercontent.com/113907476/213000631-f3b6efd1-bbfd-4dd1-b3bf-96f207f495b3.png)

10\. Doppelklick auf EI1 und Name INIT eingeben. -> Statt EI1 wird INIT bei Name und oben in Gruppe angezeigt.

![](https://user-images.githubusercontent.com/113907476/213002124-c8b80852-f823-468f-9ce7-f6dcd424b028.png)

11\. Alle INIT Events miteinander verbinden.

![](https://user-images.githubusercontent.com/113907476/213002499-a8cdbf12-ab4d-4a30-b8bd-2e161fe09f1d.png)

12\. System Configuration anlegen.

In Baum links test öffnen. System Configuration mit Doppelklick anwählen. Aus Baum rechts FORTE\_PC und Ethernet in Arbeitsbildschirm ziehen.

FORTE\_PC und Ethernet miteinander verbinden.

![](https://user-images.githubusercontent.com/113907476/213003651-761678e8-4bea-4779-978a-03b8481b1b30.png)

13\. "localhost:61499" mit Doppelklick anwählen und unbennenen in "IP auf Moped:61499" aus Beispielbild mit L11 ("192.168.188.11:61499") mit Enter bestätigen.

Gänsefüßchen müssen bleiben!

![](https://user-images.githubusercontent.com/113907476/213004986-2d8f5a90-3868-4bf8-8fd3-5d43d3dbdb71.png)

14\. Wieder links im Baum mapping wählen. Gruppe anwählen -> Gruppe wird blau und Fenster öffnet. Map To... wählen.

![](https://user-images.githubusercontent.com/113907476/213005509-e8032771-0bc3-4c84-90bb-f979fc25489a.png)

15\. Gruppe wurde gemappt. -> Gruppe wird Orange.

![](https://user-images.githubusercontent.com/113907476/213005868-ac063c60-52cf-4538-9e33-5a1adbab52fd.png)

16\. In Baum links System Configuration wählen. FORTE\_PC wählen. EMB\_RES wählen. -> Baustein START und mapping sind auf Arbeitsbildschirm.

Event INIT mit COLD aus START verbinden. (Nach verbinden kein mappen nötig.)

![](https://user-images.githubusercontent.com/113907476/213006202-94d6437b-c9fb-4f01-bdaf-10793d5ed0a8.png)

17\. Nötige Bausteine für Schaltung aus Type Libary mit gedrückter Maustaste in Arbeitsfenster ziehen (Suchfunktion kann genutz werden, Bausteine können im Arbeitsfenster kopiert werden.

![](https://user-images.githubusercontent.com/113907476/213007320-bb7b1f66-0693-4cf9-9a4d-1e3e4efeaa2b.png)

18\. Bausteine IE ; IE\_1 und QX benennen. Doppelklick auf Namen auf Baustein. Namen aus mapping aus den Bausteinen kopieren und hier einfügen. Keine Gänsefüßchen, Namen dürfen jeweils nur 1x verwendet werden, da sonst ein Fehler erscheint.

QI der Bausteine jeweils auf TRUE setzen. Steuerung miteinander verbinden.

![](https://user-images.githubusercontent.com/113907476/213008300-45d726ac-a576-4788-a6b0-3ea8505b9c1f.png)

19\. Wie bei Punkt Nr. 6 eine neue Gruppe erstellen. Gruppe benennen und Comment (Bescshreibung einfügen)

![](https://user-images.githubusercontent.com/113907476/213009045-86921bb5-2959-450d-88f1-cc40199875fa.png)

20\. Wie bei Punkt 8. Convert Group to Subapp. Wie bei Punkt 10. Event hinzufügen und in INIT unbenennen.

INIT aller Bausteine verbinden + zusätzlich Datenverbindung Q von E\_SR und OUT von DigitalOutput\_Q1 verbinden.

![](https://user-images.githubusercontent.com/113907476/213009768-12db499b-8453-4a0b-ab99-c2d33e9e22a3.png)

21\. Gruppe Bohrmaschinenschalter anwählen, Rechtsklick und mit map to mappen. -> Gruppe wird Orange.

![](https://user-images.githubusercontent.com/113907476/213011203-89febf3a-8e43-492f-9a62-de663fe08405.png)

22\. Wie bei Punkt 16. unter EMB\_RES nun auch den zweiten INIT mit COLD verbinden.

![](https://user-images.githubusercontent.com/113907476/213011415-f2b8fae7-1b15-446f-b758-a16e95f11bc6.png)

23\. Hutschienenmoped mit PC verbinden. Richtiges WLAN -> Eingabeaufforderung -> Eingabe von: ping 192.168.188.11 -t -> Verbindung wird aufgebaut: auf Antwort warten.

24\. Links im Baum Rechtsklick auf System Configuration und Deploy wählen. Meldungen bestätigen -> replace all.

![](https://user-images.githubusercontent.com/113907476/213012503-6779f658-4413-4b5c-ac7e-90646d964344.png)

25\. Steuerung sollte funktionieren. Fenster über Bausteine aufziehen, Rechtsklick dann Watch wählen und die Steuerung kann getestet und kontrolliert werden.

![](https://user-images.githubusercontent.com/113907476/213012985-5131cc59-8e43-427b-ad0d-15a306d4bc86.png)

Schalter 1 rot oder blau -> Schaltet Ausgang Q1 und LED ein. (1x drücken)

Schalter 2 blau oder rot -> Schaltet Ausgang Q1 und LED wieder aus. (1x drücken)
