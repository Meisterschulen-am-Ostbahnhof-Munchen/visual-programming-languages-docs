# USINT2USINT

<img width="1196" height="182" alt="USINT2USINT" src="https://github.com/user-attachments/assets/b8df62ab-a5f9-4c9a-a436-68fdb0e0b365" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `USINT2USINT` dient der einfachen Typkonvertierung von einem vorzeichenlosen 8-Bit Integer (USINT) zu einem anderen vorzeichenlosen 8-Bit Integer. Dieser Baustein ist besonders nützlich in Szenarien, wo eine explizite Typkonvertierung oder Wertübertragung benötigt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (USINT): Der Eingangswert, der weitergegeben werden soll.

### **Daten-Ausgänge**
- `OUT` (USINT): Der Ausgangswert, der dem Eingangswert entspricht.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock kopiert bei Auslösung des `REQ`-Ereignisses den Wert des Eingangs `IN` direkt auf den Ausgang `OUT` und bestätigt die Ausführung mit dem `CNF`-Ereignis. Es findet keine weitere Verarbeitung oder Typumwandlung statt, da Ein- und Ausgang den gleichen Datentyp (USINT) haben.

## Technische Besonderheiten
- **Einfache Implementierung**: Der Algorithmus besteht aus einer einzigen Zuweisung.
- **Keine Typkonvertierung**: Da Ein- und Ausgang den gleichen Datentyp haben, wird der Wert unverändert weitergegeben.
- **Echtzeitfähig**: Durch die minimale Verarbeitung ist der Baustein für Echtzeitanwendungen geeignet.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Wertübertragung**: Weiterleitung eines USINT-Werts ohne Änderung.
- **Typensicherheit**: Explizite Verwendung eines USINT-Werts in einer Kette von Funktionsblöcken.
- **Debugging**: Verwendung als Durchgangsbaustein zur Beobachtung von Werten.

## Vergleich mit ähnlichen Bausteinen
- **Typkonvertierungsblöcke**: Andere Konvertierungsblöcke wie `USINT_TO_INT` ändern den Datentyp, während `USINT2USINT` den Typ beibehält.
- **Durchgangsblöcke**: Ähnlich wie ein einfacher Durchgangsbaustein, aber mit expliziter Typdefinition.

## Fazit
Der `USINT2USINT`-Funktionsblock ist ein einfaches, aber nützliches Werkzeug zur Wertübertragung zwischen USINT-Variablen. Seine Stärke liegt in der Einfachheit und Echtzeitfähigkeit, was ihn ideal für grundlegende Signalverarbeitung macht.
