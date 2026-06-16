# AL_TO_AD


![AL_TO_AD](./AL_TO_AD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AL_TO_AD** ist ein Composite-FB, der einen unidirektionalen LWORD-Adapter (AL) in einen unidirektionalen DWORD-Adapter (AD) umwandelt. Er ermöglicht die Datenkonvertierung zwischen zwei unterschiedlichen Adaptertypen innerhalb der 4diac-IDE, basierend auf der IEC 61499-Norm.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- Keine (der FB besitzt keine eigenen Ereignis-Eingänge; die Ereignissteuerung erfolgt über den AL_IN-Socket)

### **Ereignis-Ausgänge**
- Keine (der FB besitzt keine eigenen Ereignis-Ausgänge; die Ereignisweiterleitung erfolgt über den AD_OUT-Plug)

### **Daten-Eingänge**
- Keine (Daten werden ausschließlich über den AL_IN-Socket bereitgestellt)

### **Daten-Ausgänge**
- Keine (Daten werden ausschließlich über den AD_OUT-Plug ausgegeben)

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|------|------|----------|--------------|
| Socket | AL_IN | Eingang | Unidirektionaler LWORD-Adapter mit einem Ereignis-Eingang (`E1`) und einem Daten-Eingang (`D1` vom Typ `LWORD`) |
| Plug   | AD_OUT | Ausgang | Unidirektionaler DWORD-Adapter mit einem Ereignis-Ausgang (`E1`) und einem Daten-Ausgang (`D1` vom Typ `DWORD`) |

## Funktionsweise
Der FB nimmt über den **AL_IN**-Socket ein LWORD-Datenwort (`D1`) zusammen mit einem Ereignis (`E1`) entgegen. Das Ereignis durchläuft den internen Funktionsblock **F_LWORD_TO_DWORD**, der die Konvertierung gemäß IEC 61131-Standard durchführt. Nach erfolgreicher Umwandlung wird das Ergebnis als DWORD (`AD_OUT.D1`) über den Plug ausgegeben, begleitet von einem Ereignis (`AD_OUT.E1`).

Die interne Netzwerkstruktur besteht aus:
- Einem **F_LWORD_TO_DWORD**-Baustein (aus der Bibliothek `iec61131::conversion`)
- Ereignisverbindung: `AL_IN.E1` → `Convert.REQ` / `Convert.CNF` → `AD_OUT.E1`
- Datenverbindung: `AL_IN.D1` → `Convert.IN` / `Convert.OUT` → `AD_OUT.D1`

## Technische Besonderheiten
- **Standardkonformität**: Die Konvertierung erfolgt über den IEC 61131-konformen FB `F_LWORD_TO_DWORD`, der eine verlustfreie Umwandlung von 64-Bit zu 32-Bit (niedrigwertige 32 Bit) vorsieht.
- **Unidirektionale Adapter**: Sowohl Eingangs- als auch Ausgangsadapter sind unidirektional ausgelegt, was die Komplexität reduziert und eine klar definierte Datenflussrichtung gewährleistet.
- **Ereignisgesteuerte Kommunikation**: Die Konvertierung wird durch ein Ereignis am Eingangsadapter getriggert; das Ergebnis wird ebenfalls ereignisgesteuert weitergereicht.
- **Einbettung in Composite-FB**: Durch die Kapselung als Composite-Baustein kann der FB einfach in größere Netze integriert werden.

## Zustandsübersicht
Der FB **AL_TO_AD** besitzt keinen eigenen Zustandsautomaten, da er als Composite-FB realisiert ist. Die Zustandslogik wird vollständig durch den internen FB **F_LWORD_TO_DWORD** abgebildet:
1. **Warten** – Kein Ereignis am Eingang vorhanden.
2. **Konvertieren** – Nach Empfang eines Ereignisses wird die Umwandlung der LWORD-Daten durchgeführt (ein Taktzyklus).
3. **Ausgeben** – Das DWORD-Ergebnis und ein Bestätigungsereignis werden am Ausgangsadapter bereitgestellt.

## Anwendungsszenarien
- **Systemintegration** – Wenn eine Komponente (z.B. eine SPS) LWORD-Daten liefert, aber ein nachgeschaltetes Modul DWORD-Daten erwartet.
- **Adapterbrücke** – In heterogenen Netzwerken, in denen Geräte unterschiedliche Datentypen für denselben physikalischen Wert verwenden.
- **Datenaufbereitung** – Vorverarbeitung von 64-Bit-Werten, die nur auf 32-Bit-Basis weiterverarbeitet werden sollen (z.B. bei Messwerten oder Zählern).

## Vergleich mit ähnlichen Bausteinen
- **WORD_TO_DWORD** – Konvertiert 16-Bit-Worte in 32-Bit-Doppelworte, jedoch auf einfachen Datentypen, nicht auf Adaptern.
- **Direkte Adapterkopplung** – Ohne Konvertierung müssten beide Systeme denselben Adaptertyp (entweder AL oder AD) verwenden, was oft nicht gegeben ist.
- **F_LWORD_TO_DWORD (isoliert)** – Dieser Baustein arbeitet nur auf Datenebene; die Adapteranbindung muss separat erfolgen. **AL_TO_AD** vereinfacht die Handhabung durch Kapselung von Adapterlogik und Konvertierung.

## Fazit
Der **AL_TO_AD**-Funktionsblock stellt eine schlanke und standardkonforme Lösung zur Umwandlung von LWORD- in DWORD-Adapterdaten dar. Durch die Kombination von Adapter- und Konvertierungslogik in einem Composite-FB wird die Wiederverwendbarkeit erhöht und die Netzwerkerstellung vereinfacht. Er eignet sich besonders für die Integration unterschiedlicher IEC 61499-Komponenten und trägt zur Modularität industrieller Automatisierungslösungen bei.