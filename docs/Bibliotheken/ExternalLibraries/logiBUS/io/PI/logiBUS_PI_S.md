# logiBUS_PI_S

```{index} single: logiBUS_PI_S
```

* * * * * * * * * *
## Einleitung
Der Funktionsblock `logiBUS_PI_S` ist ein Struktur-Datentyp (Structured Type), der für die Konfiguration eines digitalen Eingangs (PI - wahrscheinlich "Peripheral Input") innerhalb des logiBUS-Frameworks dient. Er definiert die notwendigen Parameter, um einen spezifischen physischen Pin eines I/O-Moduls oder Controllers anzusprechen. Dieser Datentyp wird typischerweise als Eingabeparameter für entsprechende IO-Funktionsblöcke verwendet.

## Schnittstellenstruktur
Als Datentyp (STRUCT) besitzt `logiBUS_PI_S` keine ereignisgesteuerten Schnittstellen, sondern definiert ausschließlich Datenfelder.

### **Daten-Eingänge**
Nicht zutreffend – dies ist ein Datentyp, kein ausführbarer Funktionsblock.

### **Daten-Ausgänge**
Nicht zutreffend – dies ist ein Datentyp, kein ausführbarer Funktionsblock.

### **Interne Struktur (Variablen)**
Die Struktur besteht aus einem einzigen Mitglied:
*   **`Pin`** (USINT, Initialwert: 255): Diese Variable spezifiziert die Hardware-Pinnummer, die als digitaler Eingang genutzt werden soll. Der Datentyp `USINT` (Unsigned Short Integer) erlaubt Werte von 0 bis 255. Der voreingestellte Initialwert 255 dient häufig als inaktiver oder undefinierter Zustand.

### **Adapter**
Nicht vorhanden.

## Funktionsweise
Der Datentyp `logiBUS_PI_S` fungiert als reiner Konfigurations-Container. Er kapselt die Information, welcher physikalische Pin angesteuert werden soll. Die eigentliche Logik zur Abfrage des Pin-Zustands liegt in den Funktionsblöcken, die eine Variable dieses Typs als Eingang erwarten (z.B. `logiBUS_PI` oder ähnliche). Diese Blöcke lesen den Wert aus dem `Pin`-Feld aus und verwenden ihn, um die entsprechende Hardware-Schnittstelle anzusteuern.

## Technische Besonderheiten
*   **Initialwert:** Der Initialwert von 255 für `Pin` ist eine gängige Praxis, um einen nicht konfigurierten oder fehlerhaften Zustand zu kennzeichnen, da Pinnummern in der Praxis meist deutlich niedriger liegen.
*   **Paketzuordnung:** Der Datentyp ist Teil des Pakets `logiBUS::io::PI`, was ihn der Kategorie der Peripherie-Eingänge (Input) innerhalb der logiBUS-Bibliothek zuordnet.
*   **Typ-Hash:** Das Attribut `eclipse4diac::core::TypeHash` mit einem leeren Wert weist darauf hin, dass für die Typkompatibilität innerhalb des Systems ein automatisch generierter Hash verwendet wird.

## Zustandsübersicht
Da es sich um einen passiven Datentyp handelt, gibt es keine Zustandsmaschine oder aktiven Zustände.

## Anwendungsszenarien
Dieser Strukturdatentyp wird verwendet, um die Konfiguration von digitalen Eingangskanälen in Steuerungsapplikationen mit logiBUS-kompatibler Hardware zentral und typsicher zu halten. Typische Anwendungen sind:
*   Konfiguration von Taster-, Schalter- oder Sensorsignalen (z.B. Endschalter, Lichtschranken).
*   Parametrierung von Funktionsblöcken, die digitale Eingänge in einem verteilten I/O-System (wie logi.BUS) auslesen.
*   Vereinfachung der Wiederverwendung und Lesbarkeit von Code, da die Pin-Konfiguration in einer benannten Struktur gebündelt ist.

## Vergleich mit ähnlichen Bausteinen
*   **Einfache Datentypen (z.B. USINT direkt):** Die Verwendung einer strukturierten `logiBUS_PI_S`-Variable ist einer direkten Verwendung einer `USINT`-Variable für die Pinnummer vorzuziehen, da sie semantisch klarer ist und bei Erweiterungen der Konfiguration (z.B. um Filterzeit oder Invertierung) einfacher erweitert werden kann, ohne alle Aufrufstellen ändern zu müssen.
*   **logiBUS_PO_S (Digitaler Ausgang):** Es existiert sehr wahrscheinlich ein komplementärer Datentyp `logiBUS_PO_S` für die Konfiguration digitaler Ausgänge (PO - Peripheral Output) mit identischer oder sehr ähnlicher Struktur.

## Fazit
Der `logiBUS_PI_S`-Datentyp ist ein grundlegender, spezifischer Konfigurationsbaustein für die Anbindung digitaler Eingangssignale in logiBUS-basierten IEC 61499-Anwendungen. Durch seine einfache, auf einen Parameter reduzierte Struktur ermöglicht er eine klare und zentrale Hardware-Konfiguration und bildet die Basis für die entsprechende Funktionalität in den ausführenden IO-Funktionsblöcken.
