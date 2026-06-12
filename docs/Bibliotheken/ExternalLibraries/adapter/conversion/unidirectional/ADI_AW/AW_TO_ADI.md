# AW_TO_ADI


![AW_TO_ADI](./AW_TO_ADI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AW_TO_ADI** ist ein Composite-Baustein, der einen unidirektionalen WORD-Adapter (AW) in einen unidirektionalen DINT-Adapter (ADI) umwandelt. Er ermöglicht die nahtlose Integration von Komponenten, die mit WORD-Daten arbeiten, in Systeme, die DINT-Werte erwarten. Intern verwendet der Baustein den Standard-Konvertierungsbaustein `F_WORD_TO_DINT` aus der IEC 61131-Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **Keine direkten Ereignis-Eingänge**  
Der Baustein besitzt keine eigenständigen Ereignis-Eingänge. Das auslösende Ereignis wird über den Socket-Adapter `AW_IN` bereitgestellt.

### **Ereignis-Ausgänge**
- **Keine direkten Ereignis-Ausgänge**  
Der Baustein besitzt keine eigenständigen Ereignis-Ausgänge. Das Ergebnis-Ereignis wird über den Plug-Adapter `ADI_OUT` weitergegeben.

### **Daten-Eingänge**
- **Keine direkten Daten-Eingänge**  
Der zu konvertierende WORD-Wert wird über den Socket-Adapter `AW_IN` empfangen.

### **Daten-Ausgänge**
- **Keine direkten Daten-Ausgänge**  
Der konvertierte DINT-Wert wird über den Plug-Adapter `ADI_OUT` ausgegeben.

### **Adapter**

| Name    | Typ                         | Richtung | Beschreibung |
|---------|-----------------------------|----------|--------------|
| `AW_IN`  | `adapter::types::unidirectional::AW`   | Socket (Eingang)  | WORD-Adapter als Eingang. Liefert das Auslöseereignis (E1) und den WORD-Datenwert (D1). |
| `ADI_OUT`| `adapter::types::unidirectional::ADI`  | Plug (Ausgang)    | DINT-Adapter als Ausgang. Gibt das Bestätigungsereignis (E1) und den konvertierten DINT-Wert (D1) weiter. |

## Funktionsweise
1. Ein eingehendes Ereignis am Socket `AW_IN.E1` triggert den internen Baustein `F_WORD_TO_DINT` über dessen Ereigniseingang `REQ`.
2. Gleichzeitig wird der WORD-Datenwert von `AW_IN.D1` an den Dateneingang `IN` von `F_WORD_TO_DINT` übergeben.
3. Nach Abschluss der Konvertierung erzeugt `F_WORD_TO_DINT` ein Bestätigungsereignis an `CNF`.
4. Dieses Ereignis wird an den Plug `ADI_OUT.E1` weitergeleitet, während der konvertierte DINT-Wert von `F_WORD_TO_DINT.OUT` an `ADI_OUT.D1` übergeben wird.

Der gesamte Ablauf erfolgt damit synchron: Ein Impuls am WORD-Adapter führt zu einem Impuls am DINT-Adapter mit dem umgewandelten Wert.

## Technische Besonderheiten
- **Reine Kopplung:** Der Baustein enthält keine eigene Logik, sondern verbindet lediglich die Adapter-Schnittstellen mit einem existierenden Konvertierungsbaustein.
- **Verwendung von IEC 61131-Standardbausteinen:** Die eigentliche Konvertierung erfolgt durch `F_WORD_TO_DINT`, der eine definierte und normierte Umrechnung bietet.
- **Unidirektionale Adapter:** Sowohl `AW_IN` als auch `ADI_OUT` sind als unidirektionale Adapter ausgelegt, d. h. sie transportieren Ereignis und Daten nur in eine Richtung.
- **Keine eigenen Zustände:** Als Composite-Baustein besitzt `AW_TO_ADI` keine eigenen internen Zustände – das Verhalten wird vollständig durch die Verschaltung der enthaltenen Elemente bestimmt.

## Zustandsübersicht
Da es sich um einen Composite-Baustein ohne eigene Zustandsmaschine handelt, existiert keine separate Zustandsübersicht. Das Laufzeitverhalten wird durch den eingebetteten `F_WORD_TO_DINT` bestimmt, der nach einem Ereignis am Eingang einen Verarbeitungsschritt durchführt und das Ergebnis ausgibt.

## Anwendungsszenarien
- **Agrartechnik:** Anbindung von Sensoren oder Aktoren, die WORD-Daten liefern (z. B. über Feldbusse mit 16‑Bit-Werten), an Steuerungen, die DINT benötigen.
- **Migration alter Systeme:** Ersatz von WORD-basierten Schnittstellen durch moderne DINT-Komponenten, ohne die gesamte Architektur umzustellen.
- **Adapter-Kapselung:** Einbinden von Bibliotheken oder Modulen, die auf unterschiedliche Datentypen ausgelegt sind, durch einen einheitlichen Adapter-Konverter.

## Vergleich mit ähnlichen Bausteinen
- **Direkte Konvertierung:** Im Gegensatz zu einem einfachen `F_WORD_TO_DINT` bietet `AW_TO_ADI` eine Adapter-basierte Schnittstelle, die eine lose Kopplung zwischen Komponenten ermöglicht.
- **Bidirektionale Konverter:** Es existieren Bausteine, die sowohl Hin- als auch Rückkonvertierung (z. B. WORD ↔ DINT) in einem Baustein vereinen. Der vorliegende Baustein ist bewusst unidirektional ausgelegt.
- **Typkonvertierung über flexible Adapter:** Andere Adapter-Konverter arbeiten mit generischen oder polymorphen Schnittstellen; dieser Baustein ist spezifisch auf WORD‑zu‑DINT festgelegt.

## Fazit
Der `AW_TO_ADI` ist ein einfacher, aber effektiver Composite-Baustein zur Umwandlung eines WORD-Adapters in einen DINT-Adapter. Durch die Verwendung eines standardisierten Konvertierungsbausteins und klarer Adapter-Schnittstellen eignet er sich besonders für den Einsatz in modularen Automatisierungslösungen, bei denen Datentypanpassungen zwischen Komponenten erforderlich sind. Seine Struktur ist transparent, leicht nachvollziehbar und erlaubt eine schnelle Integration in bestehende Projekte.