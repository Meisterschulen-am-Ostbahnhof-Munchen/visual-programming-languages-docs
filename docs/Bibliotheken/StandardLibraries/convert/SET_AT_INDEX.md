# SET_AT_INDEX

```{index} single: SET_AT_INDEX
```

<img width="1449" height="238" alt="image" src="https://github.com/user-attachments/assets/b43c3e3b-03a9-421b-a9ba-bcd4c4f00f28" />

* * * * * * * * * *
## 🎧 Podcast

* [LogiBUS zu 4diac 3.0: Die Komplette Migrationsanleitung – Kniffe, Stolpersteine und der Umstieg auf Index 1](https://podcasters.spotify.com/pod/show/logibus/episodes/LogiBUS-zu-4diac-3-0-Die-Komplette-Migrationsanleitung--Kniffe--Stolpersteine-und-der-Umstieg-auf-Index-1-e3ahcru)

## Einleitung
Der Funktionsblock `SET_AT_INDEX` dient dazu, den Wert eines Elements in einem Array an einem bestimmten Index zu setzen. Dabei muss sichergestellt werden, dass die Datentypen des zu setzenden Wertes dem Datentyp des Arrays entsprechen. Das resultierende Ausgabe-Array wird ebenfalls den Datentyp des Eingabe-Arrays aufweisen. Dieser Baustein ist nützlich für die dynamische Manipulation von Array-Daten innerhalb eines Steuerungsprogramms.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ** (Event): Ein Anforderungseingang, der die Ausführung des Funktionsblocks initiiert. Mit diesem Ereignis werden die Daten-Eingänge `IN_ARRAY`, `INDEX` und `VALUE` verarbeitet.

### **Ereignis-Ausgänge**
*   **CNF** (Event): Ein Bestätigungsausgang, der nach erfolgreicher Ausführung des Dienstes ausgelöst wird. Mit diesem Ereignis werden die Daten-Ausgänge `QO` und `OUT_ARRAY` aktualisiert.

### **Daten-Eingänge**
*   **IN_ARRAY** (ANY): Das Eingabearray, dessen Wert an einem bestimmten Index geändert werden soll. Der Datentyp `ANY` ermöglicht die Verwendung mit verschiedenen Array-Typen.
*   **INDEX** (UINT): Der nullbasierte Index des Elements im Array, dessen Wert gesetzt werden soll.
*   **VALUE** (ANY): Der Wert, der an der angegebenen Position im Array gesetzt werden soll. Der Datentyp muss mit dem Datentyp des `IN_ARRAY` übereinstimmen.

### **Daten-Ausgänge**
*   **QO** (BOOL): Ein Event-Ausgabe-Qualifizierer, der den Erfolg der Operation anzeigt. `TRUE` bei Erfolg, `FALSE` bei einem Fehler (z.B. ungültiger Index).
*   **OUT_ARRAY** (ANY): Das resultierende Array nach dem Setzen des Wertes am angegebenen Index.

### **Adapter**
Nicht vorhanden.

## Funktionsweise
Der `SET_AT_INDEX` Funktionsblock wartet auf ein `REQ`-Ereignis. Sobald dieses Ereignis eintrifft, überprüft der Baustein die übergebenen `IN_ARRAY`, `INDEX` und `VALUE`. Er versucht, den `VALUE` am `INDEX` des `IN_ARRAY` zu speichern. Bei erfolgreicher Operation wird ein neues Array erzeugt und an `OUT_ARRAY` ausgegeben, wobei `QO` auf `TRUE` gesetzt wird. Ist der angegebene `INDEX` außerhalb des gültigen Bereichs des `IN_ARRAY` oder stimmen die Datentypen von `VALUE` und den Array-Elementen nicht überein, wird die Operation möglicherweise nicht durchgeführt, und `QO` könnte `FALSE` anzeigen.

## Technische Besonderheiten
*   **Datentyp-Flexibilität:** Durch die Verwendung von `ANY` für die Array- und Wert-Parameter ist der Baustein flexibel in Bezug auf die zu verarbeitenden Datentypen. Es ist jedoch entscheidend, dass der Datentyp von `VALUE` exakt mit dem Elementdatentyp des `IN_ARRAY` übereinstimmt, um Laufzeitfehler zu vermeiden.
*   **Index-Typ:** Der `INDEX` ist vom Typ `UINT` (Unsigned Integer), was bedeutet, dass nur positive Indizes zulässig sind.
*   **Nullbasierte Indizierung:** Der Index beginnt bei 0 für das erste Element des Arrays.
*   **Fehlerbehandlung:** Die `QO`-Ausgabe dient als einfacher Indikator für den Erfolg der Operation. Eine erweiterte Fehlerbehandlung (z.B. für Index-Out-Of-Bounds) muss möglicherweise auf Anwendungsebene implementiert oder durch zusätzliche Prüfungen ergänzt werden.

## Zustandsübersicht
Der `SET_AT_INDEX` Baustein ist im Wesentlichen ein ereignisgesteuerter Baustein ohne komplexen internen Zustand. Er wartet auf ein `REQ`-Ereignis, führt die Aktion aus und gibt ein `CNF`-Ereignis aus. Seine Funktion ist direkt und reaktiv.

## Anwendungsszenarien
*   **Dynamische Konfiguration:** Ändern von Konfigurationsparametern, die in Arrays gespeichert sind, zur Laufzeit.
*   **Datenverarbeitung:** Aktualisieren von Sensor- oder Aktuatordaten, die in Arrays gesammelt werden.
*   **Algorithmische Anpassung:** Modifizieren von Look-Up-Tabellen oder Reglerparametern in Echtzeit.
*   **Benutzerinteraktion:** Setzen von Array-Werten basierend auf Benutzereingaben.

## Vergleich mit ähnlichen Bausteinen
Dieser Baustein ist komplementär zum `GET_AT_INDEX`-Baustein, der Werte aus einem Array an einem bestimmten Index auslesen würde. Er ist eine grundlegende Operation für die Array-Manipulation und bildet die Basis für komplexere Datenstruktur-Algorithmen. Im Gegensatz zu Bausteinen, die ganze Arrays kopieren oder verschieben, konzentriert sich `SET_AT_INDEX` auf die präzise Manipulation eines einzelnen Elements.

## Metadaten



| Attribut | Wert |

| :--- | :--- |

| Copyright | (c) 2014 Profactor GmbH |

| Lizenz | EPL-2.0 |

| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2014-08-05, Matthias Plasch) |

| 4diac-Paket | eclipse4diac::convert |



## Fazit



Der `SET_AT_INDEX` Funktionsblock ist ein grundlegendes, aber mächtiges Werkzeug zur Manipulation von Array-Daten in 4diac-Applikationen. Seine Flexibilität durch die `ANY`-Datentypen und die klare ereignisgesteuerte Schnittstelle machen ihn zu einem wertvollen Baustein für viele Anwendungen, die dynamische Datenstrukturen erfordern. Die korrekte Handhabung von Datentypen und Indizes ist entscheidend für seine fehlerfreie Nutzung.