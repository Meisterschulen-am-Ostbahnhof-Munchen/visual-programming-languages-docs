# ISOUSERHOME_e

* * * * * * * * * *

## Einleitung
Der Funktionsblock `ISOUSERHOME_e` ist eine **Konstantendefinition** (GlobalConstants) und kein ausführbarer Funktionsblock im klassischen Sinne. Er definiert eine Aufzählung (Enumeration) von ganzzahligen Konstanten, die zur Beschreibung der Netzwerkherkunft oder des Ziels eines Ereignisses oder einer Nachricht in einem ISOBUS-Kontext (ISO 11783) dienen. Diese Konstanten werden typischerweise in anderen Funktionsblöcken verwendet, um die Quelle oder den Empfänger von Daten innerhalb eines Controllernetzes zu kennzeichnen.

## Schnittstellenstruktur
Da es sich um eine Konstantendefinition handelt, besitzt `ISOUSERHOME_e` keine ereignis- oder datenflussbasierten Schnittstellen wie ein Standard-Funktionsblock. Stattdessen stellt es benannte Konstanten zur Verfügung.

### **Ereignis-Eingänge**
Nicht vorhanden.

### **Ereignis-Ausgänge**
Nicht vorhanden.

### **Daten-Eingänge**
Nicht vorhanden.

### **Daten-Ausgänge**
Nicht vorhanden.

### **Adapter**
Nicht vorhanden.

## Funktionsweise
Der Block definiert vier symbolische Konstanten vom Typ `SINT` (Short Integer):
*   `intern` (Wert: 0): Kennzeichnet ein internes Control Function (CF) oder einen internen Benutzer innerhalb eines Geräts oder einer logischen Einheit.
*   `network` (Wert: 1): Kennzeichnet ein externes CF oder einen externen Benutzer im Netzwerk.
*   `thisMember` (Wert: 2): Spezifiziert, dass ein Ereignis oder eine Nachricht für dieses spezifische interne CF oder diesen Benutzer bestimmt ist.
*   `notdef` (Wert: -1): Zeigt an, dass der Wert ungültig oder nicht definiert ist.

Diese Konstanten können in der gesamten Anwendung importiert und verwendet werden, um Code lesbarer und wartbarer zu machen, anstatt magische Zahlen (wie 0, 1, 2, -1) direkt zu verwenden.

## Technische Besonderheiten
*   **Typ:** `GlobalConstants` gemäß IEC 61499-1.
*   **Datenbereich:** Die Konstanten sind vom Typ `SINT` (8-Bit vorzeichenbehaftete Ganzzahl).
*   **Paket:** Der Block ist Teil des Pakets `isobus::pgn`, was auf seine Verwendung im Kontext von ISOBUS Parameter Group Numbers (PGNs) hindeutet.

## Zustandsübersicht
Nicht anwendbar, da es sich um eine statische Konstantendefinition ohne Zustandsautomaten oder Verhalten handelt.

## Anwendungsszenarien
Die Konstanten werden primär in ISOBUS-konformen Steuerungssystemen in der Landtechnik verwendet, beispielsweise in Traktoren und deren Anbaugeräten. Typische Anwendungen sind:
*   **Nachrichtenfilterung:** Ein Empfängerblock kann anhand des `ISOUSERHOME_e`-Werts entscheiden, ob eine eingehende ISOBUS-Nachricht für das eigene Gerät (`thisMember`), ein anderes Gerät im Netzwerk (`network`) oder für eine interne Verarbeitung (`intern`) bestimmt ist.
*   **Nachrichtenkonstruktion:** Ein Senderblock kann den Wert setzen, um den beabsichtigten Empfänger einer ausgesendeten Nachricht zu kennzeichnen.
*   **Statusrückmeldung:** Ein Block kann den Status `notdef` zurückgeben, wenn die Herkunft oder das Ziel einer Nachricht nicht ermittelt werden kann.

## Vergleich mit ähnlichen Bausteinen
*   **`E_SR` oder `E_RESTART`:** Dies sind ausführbare Basis-Funktionsblöcke mit Ereignislogik. `ISOUSERHOME_e` ist hingegen eine reine Datendefinition ohne Logik.
*   **Benutzerdefinierte Datentypen (DT):** Ähnlich wie ein strukturierter Datentyp (STRUCT) oder eine Aufzählung (ENUM) dient `ISOUSERHOME_e` dazu, semantische Bedeutung zu kodieren. Der Unterschied liegt in der IEC 61499-Spezifikation: `GlobalConstants` sind für unveränderliche Werte vorgesehen, die projektweit gültig sind.
*   **Direkte Verwendung von Zahlenwerten:** Die Verwendung von `ISOUSERHOME_e.intern` ist im Code deutlich aussagekräftiger und weniger fehleranfällig als die direkte Verwendung der Zahl `0`.

## Fazit
`ISOUSERHOME_e` ist ein essentielles Hilfskonstrukt für die Entwicklung klarer und wartbarer ISOBUS-Anwendungen in 4diac. Durch die Bereitstellung aussagekräftiger Konstantennamen abstrahiert es von den zugrundeliegenden numerischen Werten und verbessert so die Lesbarkeit und Robustheit des Systementwurfs. Es ist ein Baustein auf Datenebene, der die Kommunikationslogik in höheren Funktionsblöcken unterstützt.
