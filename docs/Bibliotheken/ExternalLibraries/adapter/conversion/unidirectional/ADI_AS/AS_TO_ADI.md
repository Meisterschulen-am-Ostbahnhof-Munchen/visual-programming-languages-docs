# AS_TO_ADI


![AS_TO_ADI](./AS_TO_ADI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AS_TO_ADI** wandelt einen SINT-Adapter (AS) in einen DINT-Adapter (ADI) um. Es handelt sich um einen Composite-Baustein, der eine unidirektionale, typkonvertierende Verbindung zwischen den beiden unterschiedlichen Datenadaptern herstellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Keine

### **Daten-Ausgänge**
Keine

### **Adapter**

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| Socket | Eingang | AS_IN | Adapter vom Typ `AS` (SINT, 8‑Bit signed integer) – nimmt das SINT-Signal auf. |
| Plug | Ausgang | ADI_OUT | Adapter vom Typ `ADI` (DINT, 32‑Bit signed integer) – gibt das umgewandelte DINT-Signal weiter. |

## Funktionsweise

Der Baustein verknüpft intern die Ereignis- und Datenleitungen der beiden Adapter direkt miteinander:
- Das eingehende Ereignis `E1` des Sockets `AS_IN` wird unverändert auf den Ausgangsplug `ADI_OUT` an dessen Ereignis `E1` übertragen.
- Der Datenwert `D1` aus dem SINT-Adapter (`AS_IN.D1`) wird auf den Datenport `D1` des DINT-Adapters (`ADI_OUT.D1`) weitergeleitet.

Da die Datentypen unterschiedlich sind (SINT → DINT), erfolgt eine implizite Werterhaltung: Der SINT-Wert (Wertebereich -128 … 127) wird in einen vorzeichenbehafteten 32‑Bit-Wert umkopiert (Vorzeichenerweiterung). Der Baustein selbst führt keine eigene Konvertierungslogik aus, sondern vertraut auf die durch die Adapter‑Schnittstellen definierte Typkonvertierung.

## Technische Besonderheiten

- **Composite-Baustein**: Der FB besitzt kein eigenes Verhaltensmodell (ECC), sondern nur ein internes FBNetzwerk, das die Adapter verbindet.
- **Typkonvertierung**: Die Konvertierung von SINT auf DINT erfolgt systemseitig durch die Laufzeitumgebung (Typkompatibilität bei Datenverbindungen).
- **Paket**: Der FB ist im Paket `adapter::conversion::unidirectional` eingeordnet.
- **Vollständig vorgegeben**: Die interne Verdrahtung ist fest; die Adapter müssen jeweils über einen Ereignis- und einen Datenport (`E1`, `D1`) verfügen.

## Zustandsübersicht

Da es sich um einen Composite-Baustein ohne eigene Zustandsmaschine handelt, gibt es keine Zustände oder Schritte. Der FB arbeitet rein datenflusssynchron – jedes eingehende Ereignis löst sofort die Weiterleitung aus.

## Anwendungsszenarien

- **Sensoranbindung**: Ein SINT‑Adapter (z. B. von einem 8‑Bit‑Sensor) soll an eine Steuerung angeschlossen werden, die als Schnittstelle einen DINT‑Adapter erwartet.
- **Systemintegration**: In Anlagen, in denen unterschiedliche Genauigkeitsstufen (8‑Bit vs. 32‑Bit) aufeinandertreffen, erlaubt der Baustein eine einfache, standardisierte Umwandlung.
- **Protokollanpassung**: Als Teil einer Adapter‑Kaskade, um von einem einfachen Daten‑Schnittstellenstandard auf einen leistungsfähigeren zu wechseln.

## Vergleich mit ähnlichen Bausteinen

- **AS_TO_UDI** – Konvertiert SINT nach UINT (vorzeichenloser 16‑Bit‑Integer), andere Wertebereichsinterpretation.
- **ADI_TO_AS** – Rückwärtskonvertierung von DINT nach SINT (mit möglichen Überlaufrisiken).
- **DIRECT_LINK** – Reine Durchleitung ohne Typkonvertierung, nur bei identischen Adaptertypen verwendbar.

Im Gegensatz zu universellen Konvertern (z. B. mittels `MATH`‑Bausteinen) bietet `AS_TO_ADI` eine spezialisierte, kompakte Lösung ohne zusätzliche Parametrierung.

## Fazit

Der Funktionsblock **AS_TO_ADI** realisiert eine schnelle und zuverlässige Typanpassung zwischen SINT- und DINT-Adaptern. Durch die einfache, composite‑basierte Struktur eignet er sich ideal für standardisierte Adapter‑Wandlungen in der Automatisierungstechnik, bei denen eine unidirektionale 8‑Bit → 32‑Bit‑Konvertierung benötigt wird.