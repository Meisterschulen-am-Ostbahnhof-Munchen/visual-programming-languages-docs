# AUDI_TO_AS


![AUDI_TO_AS](./AUDI_TO_AS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_TO_AS** ist ein Composite-Baustein, der einen AUDI-Adapter (Datentyp `UDINT`) in einen AS-Adapter (Datentyp `SINT`) umwandelt. Er dient als Brücke zwischen zwei unterschiedlichen Adapter-Schnittstellen und ermöglicht die verlustbehaftete Konvertierung eines vorzeichenlosen 32‑Bit‑Wertes in einen vorzeichenbehafteten 8‑Bit‑Wert. Die Umwandlung erfolgt ereignisgesteuert unter Verwendung der internen Konvertierungsfunktion `F_UDINT_TO_SINT`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine eigenständigen Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den **Socket-Adapter `AUDI_IN`**, der ein Ereignis `E1` bereitstellt.

### **Ereignis-Ausgänge**
Der FB besitzt keine eigenständigen Ereignis-Ausgänge. Das Ergebnisereignis wird über den **Plug-Adapter `AS_OUT`** mit dem Ereignis `E1` ausgegeben.

### **Daten-Eingänge**
Daten-Eingänge sind ausschließlich über den **Socket-Adapter `AUDI_IN`** verfügbar:
- **`D1`** (Datentyp `UDINT`): Der umzuwandelnde 32‑Bit‑Wert.

### **Daten-Ausgänge**
Daten-Ausgänge werden über den **Plug-Adapter `AS_OUT`** bereitgestellt:
- **`D1`** (Datentyp `SINT`): Der konvertierte 8‑Bit‑Wert (Wertebereich -128…127).  

> Hinweis: Ein `UDINT`-Wert größer als 127 wird durch die Konvertierung abgeschnitten oder interpretiert (abhängig von der Implementierung von `F_UDINT_TO_SINT`).  

### **Adapter**

| Name      | Typ                                       | Richtung | Beschreibung                     |
|-----------|-------------------------------------------|----------|----------------------------------|
| `AUDI_IN` | `adapter::types::unidirectional::AUDI`    | Socket   | Eingangsadapter (UDINT)          |
| `AS_OUT`  | `adapter::types::unidirectional::AS`      | Plug     | Ausgangsadapter (SINT)           |

## Funktionsweise
Der Baustein arbeitet als transparente Konvertierungsstufe zwischen zwei unidirektionalen Adaptern. Ein eingehendes Ereignis auf `AUDI_IN.E1` triggert den internen Funktionsblock `F_UDINT_TO_SINT`, welcher den an `AUDI_IN.D1` anliegenden `UDINT`-Wert in einen `SINT`-Wert umrechnet. Nach Abschluss der Konvertierung wird ein Ereignis auf `AS_OUT.E1` ausgegeben und der konvertierte Wert auf `AS_OUT.D1` bereitgestellt.

Der interne Ablauf ist rein kausal und benötigt keine eigenen Zustände oder Timings – die Reaktion erfolgt unmittelbar nach dem Eingangsereignis.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle**: Der FB kommuniziert ausschließlich über spezielle Adapter, was eine lose Kopplung und Wiederverwendbarkeit in unterschiedlichen Umgebungen ermöglicht.
- **Datenverlust möglich**: Da `SINT` nur 8 Bit umfasst, gehen bei einem `UDINT`-Eingangswert über 127 Informationen verloren. Die genaue Abbildung (z. B. Beschneidung oder modulare Reduktion) hängt von der internen Konvertierungsfunktion ab.
- **Keine Eigenlogik**: Der Baustein besteht vollständig aus der Verschaltung des vorhandenen Konvertierungs-FBs und zweier Adapter – ein reiner Kompositionstyp.

## Zustandsübersicht
Der FB besitzt keinen eigenen Zustandsautomaten. Er verhält sich zustandslos: Jedes eingehende Ereignis am Socket löst genau eine Ausgabe am Plug aus. Die Verarbeitung ist deterministisch und ereignissynchron.

## Anwendungsszenarien
- **Protokollanpassung**: Wenn ein Subsystem Daten als `UDINT` über einen AUDI-Adapter liefert, das Zielsystem aber nur `SINT` über einen AS-Adapter akzeptiert (z. B. bei 8‑Bit‑Aktorsteuerungen).
- **Wertebereichsreduktion**: Explizite Einschränkung eines großen Zahlenraums auf einen kleineren, um Kompatibilität mit älteren oder ressourcenbeschränkten Komponenten herzustellen.
- **Test und Simulation**: Einsatz in Testumgebungen, in denen Adapter‑Schnittstellen unterschiedlicher Datentypen aufeinander treffen.

## Vergleich mit ähnlichen Bausteinen
- **`UDINT_TO_SINT` (direkt)**: Der reine Konvertierungs-FB ohne Adaptereinbindung. `AUDI_TO_AS` kapselt diesen Baustein und fügt die spezifischen Adapter hinzu.
- Weitere Adapterkonverter (z. B. `DINT_TO_AS`, `AUDI_TO_INT`) bedienen andere Datentyp‑Kombinationen. Der vorliegende Baustein ist speziell für die Kombination `AUDI` ↔ `AS` optimiert.

## Fazit
Der Composite‑FB `AUDI_TO_AS` stellt eine einfache, aber effektive Möglichkeit dar, einen `UDINT`-basierten Adapter in einen `SINT`-basierten Adapter zu überführen. Dank der klaren Ereignissteuerung und der Verwendung einer bewährten Konvertierungsfunktion eignet er sich für alle Szenarien, in denen eine verlustbehaftete Datentyp‑Anpassung zwischen diesen beiden Adapter‑Standards erforderlich ist.