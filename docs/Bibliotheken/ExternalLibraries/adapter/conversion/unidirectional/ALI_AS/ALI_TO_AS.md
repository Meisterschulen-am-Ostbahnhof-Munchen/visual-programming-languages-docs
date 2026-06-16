# ALI_TO_AS

![ALI_TO_AS](./ALI_TO_AS.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **ALI_TO_AS** ist ein zusammengesetzter (Composite) Baustein, der einen ALI-Adapter (Datentyp LINT) in einen AS-Adapter (Datentyp SINT) umwandelt. Er kapselt die Konvertierung eines 64‑Bit‑Integerwerts in einen 8‑Bit‑Integerwert und ermöglicht so die nahtlose Integration zwischen unterschiedlichen Adapter‑Schnittstellen in der 4diac‑IDE.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine. Der FB besitzt keine separaten Ereignis‑Eingänge; die Ereignissteuerung erfolgt über die angeschlossenen Adapter.

### **Ereignis-Ausgänge**
Keine. Ereignisse werden ausschließlich über den AS‑Adapter weitergeleitet.

### **Daten-Eingänge**
Keine. Das zu konvertierende LINT‑Signal wird über den ALI‑Adapter eingelesen.

### **Daten-Ausgänge**
Keine. Das konvertierte SINT‑Signal wird über den AS‑Adapter ausgegeben.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| **ALI_IN** | `adapter::types::unidirectional::ALI` | Socket (Eingang) | Aufnahme eines LINT‑Werts (64‑Bit) über das Ereignis E1 und Datum D1. |
| **AS_OUT** | `adapter::types::unidirectional::AS` | Plug (Ausgang) | Bereitstellung des konvertierten SINT‑Werts (8‑Bit) über Ereignis E1 und Datum D1. |

## Funktionsweise
Der Baustein arbeitet nach dem Prinzip eines reinen Datenflusses ohne eigenen Zustandsautomaten.  
1. Über den **ALI_IN**‑Adapter wird das Ereignis **E1** empfangen und der zugehörige LINT‑Wert über das Datum **D1** bereitgestellt.  
2. Dieses Ereignis triggert den internen Funktionsblock **F_LINT_TO_SINT**, der die Konvertierung durchführt.  
3. Nach Abschluss der Konvertierung wird das Ereignis **CNF** des Konvertierungsbausteins aktiviert, welches wiederum das Ausgangsereignis **E1** des **AS_OUT**‑Adapters auslöst und den konvertierten SINT‑Wert über das Datum **D1** weitergibt.

Die Wandlung entspricht der IEC‑61131‑Funktion `LINT_TO_SINT`. Dabei kommt es bei Werten außerhalb des SINT‑Bereichs (-128…127) zu einem Überlauf – der Baustein führt keine zusätzliche Bereichsprüfung durch.

## Technische Besonderheiten
- **Composite‑Struktur**: Der FB setzt sich ausschließlich aus einem einzigen Konvertierungsbaustein (`F_LINT_TO_SINT`) zusammen.  
- **Unidirektionale Adapter**: Sowohl Eingangs‑ als auch Ausgangsschnittstelle sind als unidirektionale Adapter definiert – Daten fließen nur in eine Richtung.  
- **Kein Zustandsautomat**: Aufgrund der einfachen Transformation wird auf einen internen Zustandsautomaten verzichtet; die Logik erschöpft sich in der Ereignis‑Daten‑Verkettung.

## Zustandsübersicht
Der Baustein besitzt **keinen** internen Zustandsautomaten. Er arbeitet rein daten‑/ereignisgesteuert und führt bei jedem eingehenden Ereignis eine sofortige Konvertierung durch.

## Anwendungsszenarien
- **Integration von LINT‑Datenquellen** (z.B. aus hochauflösenden Zählern, Zeitstempeln) in Systeme, die nur SINT‑Werte verarbeiten (z.B. einfache Aktoransteuerungen).  
- **Brücken zwischen verschiedenen Adapter‑Typen** innerhalb einer 4diac‑Applikation, ohne dass manuelle Konvertierungsbausteine verschaltet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **ALI_TO_INT**: Wandelt LINT nach INT (16‑Bit).  
- **LINT_TO_DINT** o.ä.: Direkte Typumwandlungen ohne Adapter‑Kapselung.  
Der **ALI_TO_AS** zeichnet sich durch seine spezifische Adapter‑Schnittstelle aus; er vereinfacht die Wiederverwendung vorgefertigter Adapter‑Kopplungen in Modulen.

## Fazit
Der **ALI_TO_AS** ist ein spezialisierter Komposit‑Baustein zur verlustbehafteten Konvertierung eines LINT‑ in einen SINT‑Wert, eingebettet in eine unidirektionale Adapter‑Struktur. Er bietet eine saubere, wiederverwendbare Kapselung der Wandlungslogik und erleichtert die Anbindung unterschiedlichster Datenquellen und ‑senken innerhalb der 4diac‑Entwicklungsumgebung.