# INI_AX2


![INI_AX2](./INI_AX2.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock INI_AX2 dient dem Lesen und Speichern von REAL-Daten aus einer settings.ini-Datei über einen AX2-Adapter. Er kombiniert den INI-Baustein mit einem bidirektionalen AX2-Adapter, um Werte aus einer Konfigurationsdatei auszulesen oder zurückzuschreiben. Die Initialisierung erfolgt über das INIT-Ereignis, wobei der Abschnitt (Section) und der Schlüssel (Key) angegeben werden. Der gelesene Wert wird über den Adapter angeboten, und ein Schreibvorgang wird über das Adapter-Ereignis ausgelöst.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Beschreibung |
|------|--------------|
| INIT | Initialisierungsereignis zum Starten des Lesevorgangs. Erwartet die Parameter QI, SECTION, KEY und DEFAULT_VALUE. |

### **Ereignis-Ausgänge**
| Name | Beschreibung |
|------|--------------|
| INITO | Bestätigung der Initialisierung. Wird nach Abschluss des Lesevorgangs gesendet. Statusinformationen über QO und STATUS verfügbar. |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| QI | BOOL | Eingangsqualifikator zur Steuerung der Verarbeitung. |
| SECTION | STRING | Name des Abschnitts in der settings.ini-Datei. |
| KEY | STRING | Name des Schlüssels innerhalb des Abschnitts. |
| DEFAULT_VALUE | BOOL | Standardwert, der gelesen wird, falls der Schlüssel in der Datei nicht vorhanden ist. Voreinstellung: FALSE. |

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| QO | BOOL | Ausgangsqualifikator, signalisiert erfolgreiche Verarbeitung. |
| STATUS | STRING | Statusmeldung des Dienstes (z. B. Fehlertexte). |

### **Adapter**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| VAL | adapter::types::bidirectional::AX2 | Bidirektionaler Adapter für den Austausch von Werten. Über diesen Adapter wird der gelesene Wert als Ausgang (DO1) bereitgestellt und ein Schreibwert als Eingang (DI1) entgegengenommen. |

## Funktionsweise
Der Baustein INI_AX2 beinhaltet einen internen INI-Funktionsblock (eclipse4diac::storage::INI), der die eigentliche Dateioperation durchführt. Die Verbindungen im Netzwerk realisieren folgende Abläufe:
- Beim Eintreffen von INIT werden QI, SECTION, KEY und DEFAULT_VALUE an den INI-Baustein weitergeleitet.
- Der INI-Baustein führt einen Lesevorgang aus und gibt das Ergebnis (über VALUE) an den Adapter-Ausgang (VAL.DI1) weiter.
- Gleichzeitig wird nach erfolgreichem Lesen das Ereignis GET ausgelöst, das den Adapter-Eingang (VAL.EI1) aktiviert, um den Wert zu übermitteln.
- Ein Schreibvorgang wird initiiert, sobald der Adapter ein Ereignis EO1 sendet. Dieses Ereignis triggert das SET-Ereignis am INI-Baustein, wobei der über VAL.DO1 empfangene Wert als neuer VALUE gesetzt wird.
- Der INI-Baustein bestätigt den Schreibvorgang mit SETO und leitet dies an den Adapter zurück (VAL.EI1).
- Die Ausgänge QO und STATUS werden direkt vom INI-Baustein übernommen.

Somit können über den AX2-Adapter Lese- und Schreibzugriffe auf die settings.ini-Datei gesteuert werden.

## Technische Besonderheiten
- Der Baustein arbeitet mit einem bidirektionalen AX2-Adapter, der sowohl Werte senden als auch empfangen kann.
- Als Default-Wert wird ein BOOL-Wert verwendet, obwohl der Kommentar auf REAL-Daten hinweist. Der tatsächliche Wertetyp wird durch den Adapter bestimmt.
- Der interne INI-Baustein ist Teil der eclipse4diac-Standardbibliothek für Dateizugriffe.
- Die Verbindungen im FBNetzwerk sind so konfiguriert, dass die Ereignissteuerung zwischen Lese- und Schreibvorgängen synchronisiert wird.

## Zustandsübersicht
Der Baustein selbst besitzt keine expliziten Zustände, da er als reines Netzwerk aus unterlagerten Bausteinen realisiert ist. Die Zustandslogik wird durch den internen INI-Baustein und den Adapter bestimmt. Typische Zustände sind:
- **Initialisierung**: Warten auf INIT-Ereignis.
- **Lesen**: Verarbeitung des Lesevorgangs durch INI-Baustein.
- **Schreiben**: Verarbeitung eines Schreibbefehls über Adapter.
- **Warten**: Nach Abschluss eines Vorgangs wird auf das nächste Ereignis gewartet.

## Anwendungsszenarien
- Auslesen von Konfigurationsparametern aus einer INI-Datei in einer Automatisierungsanwendung, bei der die Werte über einen AX2-Adapter an andere Komponenten weitergegeben werden.
- Schreiben von geänderten Parametern zurück in die Datei, z. B. nach einer Benutzereingabe oder einem Algorithmus.
- Kombination mit anderen Bausteinen zur persistenten Speicherung von Einstellungen in einem IEC 61499-System.

## Vergleich mit ähnlichen Bausteinen
- Der einfache **INI**-Baustein bietet direkten Lese-/Schreibzugriff auf INI-Dateien, jedoch ohne Adapteranbindung. INI_AX2 erweitert dies um eine standardisierte AX2-Schnittstelle für den Werteaustausch.
- Andere Speicherbausteine wie **CSV** oder **JSON**-Bausteine dienen anderen Dateiformaten; INI_AX2 ist spezifisch für das INI-Format mit bidirektionalem Adapter.

## Fazit
Der Funktionsblock INI_AX2 ist eine nützliche Komponente für IEC 61499-Anwendungen, die einen einfachen Zugriff auf Konfigurationsdateien über einen AX2-Adapter benötigen. Durch die Kapselung des INI-Bausteins und die Ereignissteuerung ermöglicht er sowohl Lese- als auch Schreibvorgänge in einer settings.ini-Datei. Die Verwendung eines bidirektionalen Adapters erlaubt eine flexible Einbindung in komplexe Netzwerke.