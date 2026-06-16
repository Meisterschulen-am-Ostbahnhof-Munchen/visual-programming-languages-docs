# AD_TO_AB


![AD_TO_AB](./AD_TO_AB.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AD_TO_AB** ist ein Composite-Baustein zur unidirektionalen Konvertierung eines 32‑Bit‑DWORD-Adapters (AD) in einen 8‑Bit‑BYTE-Adapter (AB). Er dient als Brücke zwischen Komponenten, die auf unterschiedliche Datenbreiten ausgelegt sind, und kapselt die notwendige Typumwandlung gemäß IEC 61131‑3.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine direkt sichtbaren Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Adapter **AD_IN**.

### **Ereignis-Ausgänge**
Der Baustein besitzt keine direkt sichtbaren Ereignis-Ausgänge. Die Ereignisrückmeldung erfolgt über den Adapter **AB_OUT**.

### **Daten-Eingänge**
Der Baustein besitzt keine direkt sichtbaren Daten-Eingänge. Die Bereitstellung des DWORD-Werts erfolgt über den Adapter **AD_IN**.

### **Daten-Ausgänge**
Der Baustein besitzt keine direkt sichtbaren Daten-Ausgänge. Die Ausgabe des BYTE-Werts erfolgt über den Adapter **AB_OUT**.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| **AD_IN** | `adapter::types::unidirectional::AD` | Socket (Eingang) | Nimmt ein DWORD (32‑Bit) sowie ein zugehöriges Ereignis (hier `E1`) entgegen. |
| **AB_OUT** | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Gibt ein konvertiertes BYTE (8‑Bit) sowie ein quittierendes Ereignis (hier `E1`) aus. |

Beide Adapter sind unidirektional ausgelegt. Die genaue Signatur der Adapter (Anzahl der Ereignis‑ und Datenkanäle) entspricht den in der 4diac‑Bibliothek definierten Typen.

## Funktionsweise
Der Baustein arbeitet rein ereignisgesteuert und kapselt die Konvertierung mithilfe des internen Basisbausteins **F_DWORD_TO_BYTE** aus der IEC 61131‑1-Bibliothek.

1. Ein eingehendes Ereignis an **AD_IN.E1** triggert den Aufruf des internen Konvertierungsbausteins über dessen Eingang `REQ`.
2. Der Wert aus **AD_IN.D1** (DWORD) wird an den Dateneingang `IN` des Konverters weitergeleitet.
3. Nach erfolgter Wandlung signalisiert der Konverter mit `CNF` die Bereitschaft des Ergebnisses.
4. Dieses Ereignis wird an **AB_OUT.E1** weitergegeben, und der konvertierte BYTE-Wert (aus `OUT`) wird an **AB_OUT.D1** ausgegeben.

Die Umwandlung erfolgt gemäß IEC 61131‑3: Die niederwertigen 8 Bit des eingehenden DWORD werden als BYTE interpretiert.

## Technische Besonderheiten
- Der Baustein ist als Composite realisiert, d.h. er enthält keine eigene Zustandsmaschine, sondern delegiert die gesamte Logik an den internen Basisbaustein.
- Weder Pufferung noch Fehlerbehandlung sind implementiert; die Datenübergabe erfolgt direkt synchron zum Ereignis.
- Der Baustein ist für den Einsatz in Systemen vorgesehen, die eine klare Trennung zwischen Adaptern für unterschiedliche Datenbreiten erfordern.

## Zustandsübersicht
Da es sich um einen reinen Composite‑Baustein ohne eigene Zustandsmaschine handelt, existiert kein expliziter Zustandsautomat. Sein Verhalten wird vollständig durch den internen **F_DWORD_TO_BYTE**‑Baustein bestimmt, der einen einfachen Wartezustand (IDLE) und einen Verarbeitungszustand besitzt.

## Anwendungsszenarien
- **Anbindung von Sensoren/Aktoren**: Ein Sensor liefert 32‑Bit‑Rohdaten über einen AD-Adapter, die nach Konvertierung in einen 8‑Bit‑Wert an einen nachgelagerten BYTE‑Adapter weitergegeben werden.
- **Protokollwandlung**: In einer Kommunikationskette wird eine DWORD‑Schnittstelle auf eine BYTE‑Schnittstelle abgebildet, z. B. bei der Integration älterer Feldbusgeräte.
- **Reduzierung der Datenbreite**: Gezielte Extraktion des niederwertigen Bytes aus einem DWORD für nachfolgende Verarbeitungsschritte.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Konvertierung | Richtung | Adapter-Typ |
|----------|---------------|----------|-------------|
| AD_TO_AB | DWORD → BYTE  | unidirektional | AD ↔ AB |
| AD_TO_AW | DWORD → WORD  | unidirektional | AD ↔ AW |
| AW_TO_AB | WORD → BYTE   | unidirektional | AW ↔ AB |

Der **AD_TO_AB** unterscheidet sich durch die spezifische Ziel‑Datenbreite und die Verwendung der entsprechenden Adapter. Er ist speziell für Systeme ausgelegt, die mit den unidirektionalen Standardadaptern arbeiten.

## Fazit
Der Composite‑Baustein **AD_TO_AB** bietet eine einfache, ereignisgesteuerte Möglichkeit zur Konvertierung eines DWORD‑Adapters in einen BYTE‑Adapter. Er kapselt die Typumwandlung sauber und kann ohne eigene Zustandslogik in bestehende 4diac‑Netzwerke integriert werden. Die Wiederverwendung des standardisierten **F_DWORD_TO_BYTE**‑Bausteins garantiert korrektes Verhalten gemäß IEC 61131‑3.