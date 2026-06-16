# AUI_TO_AL


![AUI_TO_AL](./AUI_TO_AL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_TO_AL** ist ein zusammengesetzter (Composite) Funktionsblock, der die Konvertierung eines Adapters vom Typ AUI (basierend auf dem Datentyp UINT) in einen Adapter vom Typ AL (basierend auf dem Datentyp LWORD) ermöglicht. Er kapselt die standardisierte Konvertierungsfunktion `F_UINT_TO_LWORD` und stellt eine einfache, ereignisgesteuerte Schnittstelle für die unidirektionale Datenübertragung bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine expliziten Einzelereignis-Eingänge, da die Ereignissteuerung über die angeschlossenen Adapter erfolgt. Das Ereignis **E1** des Sockets **AUI_IN** wird intern auf den Eingang `REQ` des Konvertierungsbausteins geleitet.

### **Ereignis-Ausgänge**
Der Baustein gibt das Ereignis **E1** über den Plug **AL_OUT** aus, nachdem die Konvertierung abgeschlossen ist (Signal von `CNF` des internen Bausteins).

### **Daten-Eingänge**
Der Daten-Eingang wird ausschließlich über den Socket bereitgestellt:
* **AUI_IN.D1** (Typ: UINT) – Der zu konvertierende Wert.

### **Daten-Ausgänge**
Der Daten-Ausgang wird über den Plug bereitgestellt:
* **AL_OUT.D1** (Typ: LWORD) – Der konvertierte Wert (LWORD).

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `AUI` | **AUI_IN** | Eingang (Socket) | Eingangsadapter für den UINT-Wert und das Trigger-Ereignis. |
| `AL`  | **AL_OUT** | Ausgang (Plug)   | Ausgangsadapter für den konvertierten LWORD-Wert und das Quittungsereignis. |

## Funktionsweise
Der Funktionsblock arbeitet ereignisgesteuert:
1. Ein eingehendes Ereignis am Socket **AUI_IN.E1** (ausgelöst durch den angeschlossenen Sender) aktiviert den internen Baustein `F_UINT_TO_LWORD` über dessen Ereigniseingang `REQ`.
2. Der Wert von **AUI_IN.D1** (UINT) wird an den Dateneingang `IN` des Konvertierungsbausteins übergeben.
3. Die Konvertierung erfolgt nach IEC 61131-Standard: Ein UINT-Wert wird in einen LWORD-Wert umgewandelt (die oberen 48 Bit werden mit Nullen aufgefüllt).
4. Nach Abschluss der Konvertierung wird das Ergebnis an **AL_OUT.D1** (LWORD) weitergegeben.
5. Zeitgleich wird das Quittungsereignis von `CNF` an **AL_OUT.E1** gesendet, um dem Empfänger die Verfügbarkeit des neuen Wertes zu signalisieren.

## Technische Besonderheiten
- **Zusammengesetzter Baustein (Composite FB)**: Die Implementierung verbirgt die interne Logik und erleichtert die Wiederverwendung in größeren Adapterketten.
- **Standardkonvertierung**: Verwendet die IEC 61131-konforme Funktion `F_UINT_TO_LWORD`, dadurch portabel und plattformunabhängig.
- **Unidirektionale Übertragung**: Die Adapter sind ausschließlich für eine Datenflussrichtung ausgelegt (kein Rückkanal).
- **Keine Zustandslogik**: Der Baustein besitzt keinen eigenen Zustandsautomaten; die Ablaufsteuerung erfolgt rein über die Ereignisverkettung.

## Zustandsübersicht
Der Baustein **AUI_TO_AL** realisiert keine expliziten Zustände, da es sich um eine reine, ereignisgesteuerte Abbildung handelt. Es besteht folgender deterministischer Ablauf:
- **Warten**: Der Baustein wartet auf ein Ereignis am Eingangssocket.
- **Konvertieren**: Nach Ereigniseingang wird die Konvertierung ausgeführt.
- **Ausgeben**: Nach Abschluss wird das Ergebnis ausgegeben und der Baustein kehrt in den Wartezustand zurück.

## Anwendungsszenarien
- **Protokollanpassung**: Wenn ein Datenlieferant UINT-Werte über einen AUI-Adapter bereitstellt, aber der Verbraucher einen AL-Adapter (LWORD) erwartet.
- **Systemintegration**: In verteilten Automatisierungssystemen mit unterschiedlichen Datentypen auf der Kommunikationsebene.
- **Adapterverkettung**: Als Zwischenglied in einer Adapterkaskade zur schrittweisen Typanpassung.

## Vergleich mit ähnlichen Bausteinen
Im 4diac-Umfeld existieren weitere Konvertierungsadapter wie `AUI_TO_AB` (UINT nach BYTE) oder `AUI_TO_AW` (UINT nach WORD). **AUI_TO_AL** unterscheidet sich durch die Zielgröße LWORD (64 Bit), die für zeitkritische Anwendungen oder die Zusammenführung mehrerer Datenwörter in einen zusammenhängenden Wert genutzt wird. Es ersetzt keine universelle Typkonvertierung, sondern bietet eine dedizierte, ereignissynchrone Anpassung für die genannten Adaptertypen.

## Fazit
Der Funktionsblock **AUI_TO_AL** stellt eine saubere, standardisierte Lösung zur Umwandlung eines UINT-basierten Adapters (AUI) in einen LWORD-basierten Adapter (AL) dar. Er ist einfach zu handhaben, ereignisgesteuert und nutzt eine bewährte IEC 61131-Konvertierungsfunktion. Dank seines Composite-Charakters fügt er sich nahtlos in bestehende 4diac-Netzwerke ein und erleichtert die Integration unterschiedlicher Datenbreiten in der Automatisierungstechnik.