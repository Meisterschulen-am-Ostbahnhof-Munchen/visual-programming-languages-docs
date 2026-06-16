# AUI_UDINT_LT


![AUI_UDINT_LT](./AUI_UDINT_LT.svg)

* * * * * * * * * *
## Einleitung
Der Baustein **AUI_UDINT_LT** führt einen Kleiner-als-Vergleich zwischen zwei Werten durch. Der erste Wert wird über einen **AUI-Adapter** als Eingang bereitgestellt, der zweite Wert über einen skalaren **UDINT**-Dateneingang. Das Ergebnis des Vergleichs (Boolescher Wert) wird über einen **AX-Adapter** ausgegeben. Der Baustein wird über ein Ereignis **REQ** angestoßen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ | Service Request – startet den Vergleich. Zusammen mit diesem Ereignis wird der Datenwert **IN2** eingelesen. |

### **Ereignis-Ausgänge**
Der Baustein besitzt keine direkten Ereignisausgänge. Das Ergebnis wird über den **OUT-Adapter** (Ereignis **E1**) signalisiert.

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| IN2  | UDINT | Zweiter Vergleichswert (unsigned double integer, 32 Bit). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge. Das Ergebnis wird über den **OUT-Adapter** (Datenwert **D1**) bereitgestellt.

### **Adapter**

| Rolle | Typ | Beschreibung |
|-------|-----|--------------|
| IN1   | adapter::types::unidirectional::AUI | Erster Vergleichswert (Wert 1). Das Ereignis **E1** startet die Übergabe des Datenwertes **D1** an die interne Logik. |
| OUT   | adapter::types::unidirectional::AX   | Ausgabe des Vergleichsergebnisses: **D1** liefert `true`, wenn Wert 1 < Wert 2, andernfalls `false`. Das Ereignis **E1** signalisiert die Gültigkeit des Ergebnisses. |

## Funktionsweise
1. Der Baustein wartet auf ein Ereignis **REQ** (oder auf ein eingehendes Ereignis des **IN1**-Adapters).  
2. Mit dem Ereignis werden die beiden Werte erfasst:  
   - **IN1.D1** (vom Adapter) als erster Wert  
   - **IN2** (Dateneingang) als zweiter Wert  
3. Ein interner Funktionsbaustein **F_LT** (Typ `iec61131::comparison::F_LT`) führt den Kleiner-als-Vergleich durch.  
4. Das boolesche Ergebnis wird über **OUT.D1** ausgegeben und auf dem **OUT**-Adapter das Ereignis **E1** ausgelöst.  

## Technische Besonderheiten
- Der Baustein verwendet **Adapter** für die flexible Anbindung von Werten über standardisierte Schnittstellen (AUI für Eingang, AX für Ausgang).  
- Der Vergleich basiert auf dem IEC 61131-3 Standardvergleich für **UDINT** (vorzeichenlose 32‑Bit‑Ganzzahl).  
- Die eigentliche Vergleichslogik ist in den internen Baustein **F_LT** ausgelagert, sodass eine klare Trennung zwischen Adapteranbindung und Funktionslogik besteht.  
- Die Kommunikation mit der Umgebung erfolgt ereignisgesteuert – sowohl der Aufruf als auch die Ergebnisrückmeldung werden über Ereignisse synchronisiert.  

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine (ECC). Er verhält sich wie ein **reiner Funktionsbaustein** ohne interne Zustände:  
- Nach jedem **REQ**-Ereignis wird der Vergleich unverzögert durchgeführt und das Ergebnis am **OUT**-Adapter bereitgestellt.  
- Es gibt keine Wartezustände oder zeitlichen Verzögerungen.  

## Anwendungsszenarien
- **Grenzwertüberwachung**: Prüfen, ob ein von einem Sensor stammender Wert (über AUI) unter einem festgelegten Schwellenwert (UDINT) liegt.  
- **Steuerungslogik**: Auslösen einer Aktion, wenn eine gemessene Größe einen bestimmten Wert unterschreitet.  
- **Sicherheitsfunktionen**: Abschalten einer Anlage, wenn der Prozesswert unter einen Minimalwert fällt.  

## Vergleich mit ähnlichen Bausteinen
- **AUI_UDINT_GT**: Führt einen Größer-als-Vergleich durch (Wert 1 > Wert 2).  
- **AUI_UDINT_EQ**: Prüft auf Gleichheit (Wert 1 = Wert 2).  
- **AUI_UDINT_LE** / **AUI_UDINT_GE**: Führen Kleiner-Gleich- bzw. Größer-Gleich-Vergleiche durch.  
- Alle diese Bausteine teilen sich den gleichen Aufbau mit AUI/AX-Adaptern und unterscheiden sich nur in der internen Vergleichsfunktion.  

## Fazit
**AUI_UDINT_LT** ist ein kompakter, ereignisgesteuerter Vergleichsbaustein für UDINT-Werte. Durch die Verwendung von standardisierten Adaptern (AUI, AX) lässt er sich flexibel in industrielle Steuerungssysteme einbinden. Die klare Trennung von Adapterlogik und Vergleich erleichtert Wartung und Wiederverwendung. Der Baustein eignet sich besonders für einfache Grenzwertprüfungen und Bedingungsauswertungen in der Automatisierungstechnik.