# AB_TO_AD




![AB_TO_AD](./AB_TO_AD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AB_TO_AD** ist ein zusammengesetzter Baustein (Composite FB), der einen BYTE-Adapter (Typ `AB`) in einen DWORD-Adapter (Typ `AD`) umwandelt. Er dient als Schnittstellen-Konverter in einer unidirektionalen Kommunikation und ermöglicht die einfache Anbindung von Komponenten, die auf unterschiedlichen Datenwortbreiten basieren.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **AB_IN.E1** – Ereigniseingang vom BYTE-Adapter. Wird direkt an den DWORD-Adapter weitergeleitet.

### **Ereignis-Ausgänge**
- **AD_OUT.E1** – Ereignisausgang zum DWORD-Adapter. Entspricht dem weitergeleiteten Ereignis von **AB_IN.E1**.

### **Daten-Eingänge**
- **AB_IN.D1** – Dateneingang vom BYTE-Adapter (1 Byte Datenbreite). Wird direkt an den DWORD-Adapter weitergegeben.

### **Daten-Ausgänge**
- **AD_OUT.D1** – Datenausgang zum DWORD-Adapter (4 Byte Datenbreite). Enthält denselben Wert wie der Eingang **AB_IN.D1**, jedoch im Format eines DWORD (Double Word).

### **Adapter**
- **AB_IN** (Socket) – Unidirektionaler BYTE-Adapter (Typ `AB`), der als Eingang dient.
- **AD_OUT** (Plug) – Unidirektionaler DWORD-Adapter (Typ `AD`), der als Ausgang dient.

## Funktionsweise
Der Baustein verbindet die Schnittstellen eines BYTE-Adapters (Eingang) mit denen eines DWORD-Adapters (Ausgang). Jedes eingehende Ereignis (**E1**) wird ohne Verzögerung oder Bearbeitung an den Ausgang weitergeleitet. Ebenso wird der eingehende Datenwert (**D1**) unverändert, aber als 4-Byte-DWORD, an den Ausgang übergeben. Der Baustein besitzt keine eigene Logik; er fungiert ausschließlich als Durchreiche („Passthrough“) zwischen den beiden Adaptertypen.

## Technische Besonderheiten
- **Unidirektionalität:** Der Baustein unterstützt nur eine Datenflussrichtung vom BYTE-Adapter zum DWORD-Adapter. Eine Rückwärtsübertragung ist nicht vorgesehen.
- **Datenbreitenanpassung:** Der eingehende BYTE-Wert (1 Byte) wird in einen DWORD-Wert (4 Byte) eingebettet. Das niederwertigste Byte des DWORD entspricht dem eingehenden BYTE; die höherwertigen Bytes werden auf Null gesetzt (bzw. bleiben je nach Implementierung des Zieladapters erhalten).
- **Einfache Kopplung:** Der FB ist ein reiner Verbindungsbaustein im FBNetwork und benötigt keine eigene Zustandsmaschine oder Algorithmen.

## Zustandsübersicht
Der Baustein verfügt über keine eigene Zustandslogik, da er ausschließlich als Verkabelung zwischen den Adaptern fungiert. Sein Verhalten ist ereignisgesteuert: Jedes Ereignis am Eingang wird sofort zum Ausgang durchgereicht.

## Anwendungsszenarien
- **Systemintegration:** Wenn ein Subsystem mit BYTE-Adaptern arbeitet, ein nachfolgendes Subsystem jedoch DWORD-Adapter erwartet, kann `AB_TO_AD` als Konverter zwischengeschaltet werden.
- **Datenaggregation:** Mehrere solcher Bausteine können verwendet werden, um einzelne Bytes zu einem DWORD zusammenzuführen, falls die Quelladapter jeweils nur ein Byte liefern.
- **Protokollanpassung:** In Feldbus- oder Sensoranbindungen, bei denen die Datenbreite zwischen Komponenten wechselt, dient der Baustein als einfache Anpassungsschicht.

## Vergleich mit ähnlichen Bausteinen
Es existieren analoge Konverterbausteine für andere Datenbreiten, z. B. `AB_TO_WORD` (BYTE nach WORD) oder `WORD_TO_DWORD`. Der vorliegende Baustein spezialisiert sich auf die Kombination `AB` → `AD` und ist daher ideal für den direkten Ersatz oder die Kopplung entsprechender Adapter. Im Gegensatz zu komplexeren Konvertern mit Datenmanipulation oder Puffern arbeitet er verzögerungsfrei und ohne zusätzliche Logik.

## Fazit
`AB_TO_AD` ist ein schlanker, klar strukturierter Konverterbaustein, der die unidirektionale Umwandlung eines BYTE-Adapters in einen DWORD-Adapter ermöglicht. Durch seine einfache Durchreichung eignet er sich hervorragend für die schnelle Integration unterschiedlicher Schnittstellen in IEC 61499-basierten Steuerungssystemen, ohne zusätzliche funktionale Komplexität einzuführen.