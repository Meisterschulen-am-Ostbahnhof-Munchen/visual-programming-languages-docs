# GET_AT_INDEX

![GET_AT_INDEX](https://github.com/user-attachments/assets/a71d5bb4-234d-4c70-9cf5-b20eead51d0f)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `GET_AT_INDEX` dient dazu, einen Wert aus einem Array an einem bestimmten Index auszulesen. Der Datentyp des Arrays muss dabei mit dem Datentyp des Ausgangswertes übereinstimmen. Dieser Baustein ist besonders nützlich, wenn auf bestimmte Elemente in einem Array dynamisch zugegriffen werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dienst-Anforderung. Löst die Ausführung des Funktionsblocks aus. Wird mit den Daten-Eingängen `IN_ARRAY` und `INDEX` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Dienstleistung. Wird mit den Daten-Ausgängen `QO` und `OUT` verknüpft.

### **Daten-Eingänge**
- **IN_ARRAY**: Eingabe-Array, aus dem ein Wert gelesen werden soll. Der Datentyp ist `ANY` (beliebig).
- **INDEX**: Index, an dem der Wert aus dem Array gelesen werden soll. Der Datentyp ist `UINT` (vorzeichenlose Ganzzahl).

### **Daten-Ausgänge**
- **QO**: Qualifikator des Ereignis-Ausgangs. Gibt an, ob die Operation erfolgreich war (`BOOL`).
- **OUT**: Der aus dem Array gelesene Wert. Der Datentyp ist `ANY` und muss mit dem Datentyp des Eingabe-Arrays übereinstimmen.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `GET_AT_INDEX` wird durch das Ereignis `REQ` aktiviert. Dabei werden die Eingabedaten `IN_ARRAY` (das Array) und `INDEX` (der gewünschte Index) verarbeitet. Der Funktionsblock liest den Wert an der angegebenen Position im Array und gibt ihn über den Ausgang `OUT` aus. Gleichzeitig wird der Qualifikator `QO` gesetzt, um den Erfolg der Operation anzuzeigen. Die Bestätigung der Operation erfolgt über das Ereignis `CNF`.

## Technische Besonderheiten
- Der Datentyp des Arrays (`IN_ARRAY`) und des Ausgangswertes (`OUT`) muss identisch sein.
- Der Index (`INDEX`) muss eine gültige Position im Array darstellen, andernfalls kann das Verhalten undefiniert sein.
- Der Funktionsblock unterstützt beliebige Datentypen (`ANY`), was eine hohe Flexibilität ermöglicht.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Dynamischer Zugriff auf Array-Elemente in Steuerungsanwendungen.
- Verwendung in Szenarien, bei denen der Index zur Laufzeit berechnet wird.
- Integration in komplexere Algorithmen, die Array-Manipulation erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu statischen Array-Zugriffen bietet `GET_AT_INDEX` die Möglichkeit, den Index dynamisch zu bestimmen.
- Ähnliche Bausteine wie `ARRAY_ACCESS` könnten spezifischere Datentypen unterstützen, sind aber weniger flexibel.

## Fazit
Der `GET_AT_INDEX`-Funktionsblock ist ein vielseitiges Werkzeug für den dynamischen Zugriff auf Array-Elemente. Seine Flexibilität in Bezug auf Datentypen macht ihn besonders nützlich in verschiedenen Anwendungsfällen. Allerdings sollte sichergestellt werden, dass der verwendete Index innerhalb der Array-Grenzen liegt, um undefiniertes Verhalten zu vermeiden.
