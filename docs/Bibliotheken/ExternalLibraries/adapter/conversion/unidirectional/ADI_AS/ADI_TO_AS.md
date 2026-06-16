# ADI_TO_AS


![ADI_TO_AS](./ADI_TO_AS.svg)

* * * * * * * * * *
## Einleitung
Der Composite‑Funktionsblock **ADI_TO_AS** dient der Konvertierung eines **DINT‑Adapter‑Signals** (Typ `ADI`) in ein **SINT‑Adapter‑Signal** (Typ `AS`). Er wird eingesetzt, wenn ein Daten‑ und Ereignisaustausch über unidirektionale Adapter erfolgen soll und eine Anpassung des Datentyps von DINT (32‑Bit Signed Integer) auf SINT (8‑Bit Signed Integer) erforderlich ist.

## Schnittstellenstruktur
### **Ereignis‑Eingänge**
Keine separaten Ereignis‑Eingänge – die Ereignisansteuerung erfolgt über den integrierten **ADI‑IN‑Adapter** (Socket).

### **Ereignis‑Ausgänge**
Keine separaten Ereignis‑Ausgänge – die Ereignisweiterleitung erfolgt über den integrierten **AS‑OUT‑Adapter** (Plug).

### **Daten‑Eingänge**
Keine separaten Daten‑Eingänge – der Datenwert wird über den **ADI‑IN‑Adapter** bereitgestellt.

### **Daten‑Ausgänge**
Keine separaten Daten‑Ausgänge – der konvertierte Wert wird über den **AS‑OUT‑Adapter** ausgegeben.

### **Adapter**

| Adapter | Richtung | Typ | Kommentar |
|---------|----------|-----|-----------|
| **ADI_IN** | Socket (Eingang) | `adapter::types::unidirectional::ADI` | DINT‑Adapter‑Eingang |
| **AS_OUT** | Plug (Ausgang)   | `adapter::types::unidirectional::AS`  | SINT‑Adapter‑Ausgang |

Der **ADI‑IN‑Adapter** stellt eine Ereignisschnittstelle `E1` und eine Datenschnittstelle `D1` (Typ DINT) bereit. Der **AS‑OUT‑Adapter** bietet entsprechend `E1` und `D1` (Typ SINT).

## Funktionsweise
Im Inneren des Composite‑Bausteins wird ein einzelner Funktionsblock `Convert` vom Typ `iec61131::conversion::F_DINT_TO_SINT` verwendet. Die Signalverbindungen sind:

1. Ein eingehendes Ereignis am **ADI‑IN‑Adapter** (`E1`) triggert den **Convert‑FB** über dessen Ereigniseingang `REQ`.
2. Gleichzeitig wird der DINT‑Wert vom Adapter‑Datenport `ADI_IN.D1` an den **Convert‑Eingang** `IN` übergeben.
3. Nach Abschluss der Konvertierung erzeugt **Convert** ein Ereignis an seinem Ausgang `CNF`.
4. Dieses Ereignis wird direkt an den **AS‑OUT‑Adapter** (`E1`) weitergeleitet.
5. Der konvertierte SINT‑Wert liegt am **Convert‑Ausgang** `OUT` an und wird an den Adapter‑Datenport `AS_OUT.D1` übergeben.

Damit ist eine vollständige, ereignisgesteuerte Umwandlung von DINT nach SINT über die Adapter‑Schnittstellen realisiert.

## Technische Besonderheiten
- **Lizenz und Herkunft:** Der Baustein unterliegt der **Eclipse Public License 2.0** und stammt von der **HR Agrartechnik GmbH** (Version 1.0, Autor: Franz Höpfinger, Stand: 2026‑02‑17).
- **Abhängigkeit:** Er nutzt den Bibliotheksbaustein `iec61131::conversion::F_DINT_TO_SINT` aus dem IEC‑61131‑Konvertierungspaket.
- **Composite‑Struktur:** Es werden keine eigenen Zustände oder Algorithmen definiert – die gesamte Logik wird durch das innere Netzwerk ausgeführt.
- **Paketzuordnung:** Der Baustein ist im Paket `adapter::conversion::unidirectional` organisiert.

## Zustandsübersicht
Als Composite‑Funktionsblock besitzt **ADI_TO_AS** keine eigene Zustandsmaschine. Das Verhalten ergibt sich ausschließlich aus der Abarbeitung des eingebetteten FBs `F_DINT_TO_SINT` und den fest verdrahteten Verbindungen.

## Anwendungsszenarien
- **Adapter‑Typkonvertierung:** Wenn eine Komponente (z. B. ein Sensor oder Aktor) über einen unidirektionalen DINT‑Adapter kommuniziert, das Zielsystem jedoch einen SINT‑Adapter erwartet.
- **Datenbereichsreduktion:** Anwendungen, bei denen ein 32‑Bit‑Wert in einen 8‑Bit‑Wert umgewandelt werden muss, z. B. zur Ansteuerung einfacher Peripherie mit begrenzter Auflösung.
- **Schnittstellenanpassung:** Einbindung in eine Toolchain, die auf das unidirektionale Adapter‑Konzept von 4diac aufbaut und eine saubere Trennung von Ereignis‑ und Datenflüssen erfordert.

## Vergleich mit ähnlichen Bausteinen
Es existieren weitere Adapter‑Konvertierungsbausteine wie z. B. `ADI_TO_AI` (DINT → INT) oder `ADI_TO_ADI` (identische Durchleitung). Der **ADI_TO_AS** unterscheidet sich durch die spezifische Zieltypumsetzung auf SINT. Gemeinsam ist allen die einheitliche Adapter‑Schnittstelle und die ereignisgesteuerte Verarbeitung mittels eines enthaltenen Konvertierungs‑FBs.

## Fazit
Der **ADI_TO_AS** ist ein kompakter, fertig vorgefertigter Composite‑Baustein, der die Umwandlung eines DINT‑Adapter‑Signals in ein SINT‑Adapter‑Signal zuverlässig und einfach ermöglicht. Er ist ideal für alle Anwendungen, die eine saubere Typkonvertierung im Rahmen des 4diac‑Adapterkonzepts benötigen, ohne dass separate Konvertierungslogik manuell implementiert werden muss. Dank der Lizenz unter EPL‑2.0 kann er in eigenen Projekten frei genutzt und angepasst werden.