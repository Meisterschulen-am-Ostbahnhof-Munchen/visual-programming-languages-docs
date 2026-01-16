# GET_AT_INDEX

<img width="1341" height="212" alt="image" src="https://github.com/user-attachments/assets/05b8aa7e-9c77-4a15-8787-2bd7d986a846" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsblock (FB) dient dazu, einen Wert aus einem Array an einer spezifischen Indexposition abzurufen. Eine wichtige Voraussetzung für die korrekte Funktionsweise ist, dass der Datentyp des Eingabe-Arrays mit dem Datentyp des Ausgabewerts übereinstimmt. Es handelt sich um einen grundlegenden Baustein für den Zugriff auf Array-Elemente.

## Schnittstellenstruktur
Der `GET_AT_INDEX`-Funktionsblock verfügt über eine klar definierte Schnittstellenstruktur mit Ereignis- und Dateneingängen sowie -ausgängen.

### **Ereignis-Eingänge**
*   **REQ** (Typ: `Event`)
    *   Dienstanfrage zur Ausführung des Funktionsblocks.
    *   Ist verknüpft mit den Daten-Eingängen `IN_ARRAY` und `INDEX`, die bei der Auslösung des Ereignisses gelesen werden.

### **Ereignis-Ausgänge**
*   **CNF** (Typ: `Event`)
    *   Bestätigung des angefragten Dienstes nach erfolgreicher Verarbeitung.
    *   Ist verknüpft mit den Daten-Ausgängen `QO` und `OUT`, die nach der Verarbeitung bereitgestellt werden.

### **Daten-Eingänge**
*   **IN_ARRAY** (Typ: `ANY`)
    *   Das Eingabe-Array, aus dem ein Wert abgerufen werden soll. Der Datentyp ist generisch (`ANY`), muss aber zur Ausgabe passen.
*   **INDEX** (Typ: `UINT`)
    *   Der Index (Position) innerhalb des `IN_ARRAY`, von dem der Wert abgerufen werden soll.

### **Daten-Ausgänge**
*   **QO** (Typ: `BOOL`)
    *   Ein Qualifizierer für den Ereignis-Ausgang, der typischerweise den Erfolg oder Misserfolg des Vorgangs anzeigt (z.B. `TRUE` bei Erfolg, `FALSE` bei Fehler).
*   **OUT** (Typ: `ANY`)
    *   Der abgerufene Wert aus dem `IN_ARRAY` an der angegebenen `INDEX`-Position. Der Datentyp ist generisch (`ANY`).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Wenn ein `REQ`-Ereignis am Eingang des Funktionsblocks empfangen wird, liest der `GET_AT_INDEX`-FB die aktuellen Werte der Daten-Eingänge `IN_ARRAY` und `INDEX`. Er greift dann auf das `IN_ARRAY` zu und extrahiert den Wert an der durch `INDEX` angegebenen Position. Dieser abgerufene Wert wird an den Daten-Ausgang `OUT` weitergeleitet. Gleichzeitig wird der `QO`-Ausgang entsprechend dem Ergebnis des Vorgangs gesetzt (z.B. `TRUE` bei erfolgreichem Zugriff). Abschließend wird das `CNF`-Ereignis ausgelöst, um die Beendigung des Dienstes zu signalisieren.

## Technische Besonderheiten
*   **Datentyp-Übereinstimmung**: Es ist entscheidend, dass der Datentyp des Eingabe-Arrays (`IN_ARRAY`) mit dem erwarteten Datentyp des abgerufenen Werts (`OUT`) kompatibel ist, um Typfehler zu vermeiden.
*   **Indexbereich**: Der Wert von `INDEX` muss innerhalb der gültigen Grenzen des `IN_ARRAY` liegen, um Laufzeitfehler oder undefiniertes Verhalten zu verhindern. Eine Überprüfung des Indexbereichs muss ggf. durch vor- oder nachgeschaltete Logik sichergestellt werden.
*   **ANY-Typ**: Die Verwendung des `ANY`-Typs für `IN_ARRAY` und `OUT` macht den Baustein sehr flexibel, erfordert aber eine sorgfältige Typisierung in der Anwendung.

## Zustandsübersicht
Der `GET_AT_INDEX`-Funktionsblock ist im Wesentlichen zustandslos in Bezug auf die Datenhaltung. Seine Zustände beschränken sich auf den Ausführungszyklus:
1.  **Bereit**: Wartet auf ein `REQ`-Ereignis.
2.  **Ausführend**: Liest Eingänge, führt den Array-Zugriff durch und setzt Ausgänge.
3.  **Abgeschlossen**: Löst das `CNF`-Ereignis aus und kehrt in den Zustand "Bereit" zurück.

## Anwendungsszenarien
*   **Datenprotokollierung und -analyse**: Abrufen spezifischer Messwerte aus einem Zeitreihen-Array.
*   **Konfigurationsverwaltung**: Lesen einzelner Parameter aus einem Array von Konfigurationswerten.
*   **Abarbeitung von Listen**: Sequenzielles oder zufälliges Abrufen von Elementen aus einer Liste von Aufgaben oder Objekten.
*   **Robotersteuerung**: Zugriff auf Positionen oder Bewegungsparameter, die in Arrays gespeichert sind.
*   **Visualisierung**: Abrufen von Datenpunkten für die Darstellung auf einer Benutzeroberfläche.

## Vergleich mit ähnlichen Bausteinen
Der `GET_AT_INDEX`-Baustein ist ein spezialisierter Baustein für den Array-Zugriff. Er unterscheidet sich von:
*   **`SET_AT_INDEX`**: Einem komplementären Baustein, der Werte an einer bestimmten Array-Position setzt, anstatt sie abzurufen.
*   **Array-Iteratoren**: Bausteinen, die typischerweise das gesamte Array durchlaufen, anstatt nur ein einzelnes Element über einen direkten Index abzurufen.
*   **Allgemeinen Datenmanipulationsbausteinen**: Die nicht speziell für Array-Zugriffe konzipiert sind, sondern allgemeinere Operationen (z.B. Addition, Vergleich) durchführen.

`GET_AT_INDEX` füllt somit eine grundlegende Lücke für den direkten, indizierten Lesezugriff auf Array-Datenstrukturen.

## Metadaten



| Attribut | Wert |

| :--- | :--- |

| Copyright | (c) 2014 Profactor GmbH |

| Lizenz | EPL-2.0 |

| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2014-07-11, Matthias Plasch) |

| 4diac-Paket | eclipse4diac::convert |



## Fazit



Der `GET_AT_INDEX`-Funktionsblock ist ein elementarer und flexibler Baustein, der den direkten und indizierten Zugriff auf Array-Elemente ermöglicht. Seine Einfachheit und die Unterstützung generischer Datentypen (`ANY`) machen ihn zu einem vielseitigen Werkzeug in zahlreichen Automatisierungs- und Steuerungsanwendungen, bei denen Daten in geordneten Listen oder Tabellen vorliegen. Die korrekte Anwendung erfordert lediglich die Beachtung der Datentyp-Kompatibilität und des gültigen Indexbereichs.
