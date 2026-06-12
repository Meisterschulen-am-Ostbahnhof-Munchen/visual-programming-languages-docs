# AUI_TO_AI


![AUI_TO_AI](./AUI_TO_AI.svg)

* * * * * * * * * *
## Einleitung
Composite FB zur Umwandlung eines AUI‑ (UINT) Adapters in einen AI‑ (INT) Adapter. Er kapselt die Konvertierung mittels des Bausteins `F_UINT_TO_INT` und stellt eine einheitliche Adapter‑Schnittstelle bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge auf FB‑Ebene. Das Ereignis wird über den **Socket AUI_IN** (Ereignis `E1`) empfangen.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge auf FB‑Ebene. Das Ereignis wird über den **Plug AI_OUT** (Ereignis `E1`) ausgegeben.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge auf FB‑Ebene. Der UINT‑Wert wird über den **Socket AUI_IN** (Datenpunkt `D1`) bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge auf FB‑Ebene. Der INT‑Wert wird über den **Plug AI_OUT** (Datenpunkt `D1`) ausgegeben.

### **Adapter**
- **Socket AUI_IN** (Typ: `adapter::types::unidirectional::AUI`) – Empfängt UINT‑Daten und ein Ereignis.
- **Plug AI_OUT** (Typ: `adapter::types::unidirectional::AI`) – Sendet INT‑Daten und ein Ereignis.

## Funktionsweise
Der Baustein verbindet den AUI‑Adapter‑Socket über ein FBNetwork mit einem Konvertierungs‑FB vom Typ `F_UINT_TO_INT`:

1. Das Ereignis `E1` des AUI_IN‑Adapters triggert den Konvertierungs‑FB am **REQ**‑Eingang.
2. Der Konvertierungs‑FB liest den UINT‑Wert vom Datenpunkt `AUI_IN.D1` und konvertiert ihn nach INT.
3. Nach der Konvertierung sendet der FB ein Bestätigungsereignis über **CNF**, das das Ereignis `E1` des AI_OUT‑Adapters auslöst.
4. Der konvertierte INT‑Wert wird über den Datenpunkt `AI_OUT.D1` an den AI‑Adapter übergeben.

## Technische Besonderheiten
- Composite‑FB ohne eigene Zustandslogik (kein ECC).
- Verwendet den Standard‑Baustein `iec61131::conversion::F_UINT_TO_INT` für die Typkonvertierung.
- Enthält Lizenzhinweise gemäß Eclipse Public License 2.0.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustandsautomaten. Die Steuerung erfolgt rein durch die Ereignisverkettung im FBNetwork.

## Anwendungsszenarien
- Integration einer Komponente, die einen AUI‑Adapter (UINT) liefert, in ein System, das einen AI‑Adapter (INT) erwartet.
- Kapselung der Konvertierung, um die Wiederverwendung zu erleichtern und die Netzwerkstruktur übersichtlich zu halten.

## Vergleich mit ähnlichen Bausteinen
- **AUI_TO_AI** wandelt UINT → INT.
- Ein analoger Baustein **AI_TO_AUI** würde die umgekehrte Konvertierung (INT → UINT) bereitstellen.
- Im Gegensatz zu direkten Typkonvertierungs‑FBs (wie `F_UINT_TO_INT`) arbeitet dieser Baustein auf Adapterebene und fügt sich nahtlos in IEC 61499‑Adapterkonzepte ein.

## Fazit
Der **AUI_TO_AI**‑Baustein bietet eine einfache und gekapselte Lösung, um AUI‑Adapter in AI‑Adapter zu konvertieren. Er erleichtert die Interoperabilität zwischen Komponenten mit unterschiedlichen Datentypen und trägt zu einer sauberen, modularen Systemarchitektur bei.