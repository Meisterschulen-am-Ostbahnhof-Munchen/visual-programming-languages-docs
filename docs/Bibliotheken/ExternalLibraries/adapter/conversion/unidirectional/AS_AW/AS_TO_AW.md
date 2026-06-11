# AS_TO_AW


![AS_TO_AW](./AS_TO_AW.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AS_TO_AW** ist ein zusammengesetzter Baustein (Composite FB), der einen unidirektionalen **SINT**-Adapter (AS) in einen unidirektionalen **WORD**-Adapter (AW) umwandelt. Er dient als Brücke zwischen verschiedenen Adapter-Typen und ermöglicht die Weiterverarbeitung von SINT-Signalen als WORD-Daten in einer 4diac-Umgebung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine direkten Ereignis-Eingänge.*  
Der Baustein besitzt einen **Socket** vom Typ `AS`, der indirekt einen Ereignis-Eingang bereitstellt:
- **AS_IN.E1** – Ereignis-Eingang über den Socket; ein eingehendes Ereignis löst die Konvertierung aus.

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge.*  
Der Baustein besitzt einen **Plug** vom Typ `AW`, der indirekt einen Ereignis-Ausgang bereitstellt:
- **AW_OUT.E1** – Ereignis-Ausgang über den Plug; nach erfolgreicher Konvertierung wird ein Ereignis gesendet.

### **Daten-Eingänge**
- **AS_IN.D1** (`SINT`) – Eingangsdatenwert des AS-Sockets; der zu konvertierende SINT-Wert.

### **Daten-Ausgänge**
- **AW_OUT.D1** (`WORD`) – Ausgangsdatenwert des AW-Plugs; der konvertierte WORD-Wert.

### **Adapter**
| Typ | Name | Richtung | Kommentar |
|------|------|----------|-----------|
| `AS` (unidirektional) | **AS_IN** | Socket (Eingang) | SINT Adapter Eingang |
| `AW` (unidirektional) | **AW_OUT** | Plug (Ausgang) | WORD Adapter Ausgang |

## Funktionsweise

Der Baustein enthält eine interne Instanz des Konvertierungsbausteins `iec61131::conversion::F_SINT_TO_WORD`.  
Die Verarbeitung erfolgt ereignisgesteuert:

1. Ein Ereignis am **AS_IN.E1** (Socket) triggert den internen Baustein über seinen `REQ`-Eingang.
2. Gleichzeitig wird der Wert von **AS_IN.D1** (`SINT`) an den `IN`-Eingang des Konverters weitergeleitet.
3. Der Konverter `F_SINT_TO_WORD` führt die Typumwandlung durch und signalisiert die Fertigstellung über seinen `CNF`-Ausgang.
4. Dieses Ereignis wird an **AW_OUT.E1** (Plug) weitergegeben, und der konvertierte `WORD`-Wert steht an **AW_OUT.D1** zur Verfügung.

Somit wird eine zuverlässige, einmalige Konvertierung bei jeder Ereignisankunft durchgeführt.

## Technische Besonderheiten

- **Composite FB**: Der Baustein nutzt die Composite-Funktionalität von 4diac, um einen vorhandenen Konvertierungsbaustein (`F_SINT_TO_WORD`) in eine Adapter-Hülle zu integrieren.
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt, d.h. nur eine Daten- und Ereignisrichtung wird unterstützt.
- **IEC 61131-3 Konvertierung**: Die eigentliche Typumwandlung erfolgt nach IEC 61131-3 Standard, was die Kompatibilität mit anderen Systemen erleichtert.
- **Copyright-Vermerk**: Der Baustein enthält einen Copyright-Hinweis (EPL 2.0), der die Nutzung und Weiterverbreitung regelt.

## Zustandsübersicht

Da der Baustein aus einem internen FB mit REQ/CNF-Handshake besteht, lässt sich der Ablauf wie folgt beschreiben:

| Zustand | Beschreibung |
|---------|--------------|
| **Idle** | Warten auf ein Ereignis am AS_IN.E1 |
| **Busy** | Konvertierung läuft (interner FB aktiv) |
| **Done** | Konvertierung abgeschlossen, Ereignis an AW_OUT.E1 gesendet |

Der Baustein ist nicht zustandsbehaftet im Sinne eines eigenen Zustandsautomaten – der interne FB realisiert die Zustandslogik.

## Anwendungsszenarien

- **Signalanpassung**: Ein Sensor liefert Daten als SINT (z.B. 8-Bit-Wert), das nachgeschaltete System erwartet jedoch WORD (16-Bit). Der AS_TO_AW übernimmt die Umwandlung.
- **Adapter-Integration**: In einem heterogenen Steuerungssystem müssen verschiedene Adapter-Typen miteinander verbunden werden. Der Baustein fungiert als „Übersetzer“ zwischen AS- und AW-Schnittstellen.
- **Test- und Simulationsumgebungen**: Zum Überbrücken von Adapter-Inkompatibilitäten während der Entwicklung oder beim Testen von Funktionsbausteinen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| **AS_TO_AW** | SINT → WORD | Spezifische Konvertierung für unidirektionale Adapter |
| **Allgemeine Konverter** (z.B. `F_SINT_TO_WORD`) | reine Datenkonvertierung ohne Adapter-Kapselung | AS_TO_AW bietet eine fertige Adapter-Schnittstelle und kann direkt in Adapter basierten Netzwerken verwendet werden |
| **Andere Adapter-Konverter** (z.B. `BOOL_TO_BYTE`) | andere Datentypen | AS_TO_AW ist auf SINT ↔ WORD spezialisiert |

## Fazit

Der **AS_TO_AW** ist ein nützlicher, kompakter Konvertierungsbaustein, der die Umwandlung von einem SINT-Adapter (AS) zu einem WORD-Adapter (AW) nahtlos in die 4diac-IDE integriert. Durch die Verwendung des standardisierten IEC 61131-3 Konverters und die unidirektionale Adapter-Technologie ermöglicht er eine flexible und zuverlässige Signalumsetzung in Automatisierungsprojekten.