package com.mycompany.javaprojectl3;

public class OpenFoodFacts {
    
    public static String getNutriScore(String bar_code) throws java.net.MalformedURLException, java.io.IOException {
        String nutriScoreGrade = "\0";
        java.net.URL url = new java.net.URL("http://ssl-api.openfoodfacts.org/api/v0/product/" + bar_code + ".json");
        java.net.URLConnection connection = (java.net.URLConnection) url.openConnection();
        javax.json.stream.JsonParserFactory factory = javax.json.Json.createParserFactory(null);
        // Effective connection with the service:
        javax.json.stream.JsonParser parser = factory.createParser(connection.getInputStream());
        while (parser.hasNext()) {
            javax.json.stream.JsonParser.Event event = parser.next();
            if (event == javax.json.stream.JsonParser.Event.KEY_NAME && parser.getString().equals("nutriscore_grade")) {
                while (parser.hasNext()) {
                    event = parser.next();
                    if (event == javax.json.stream.JsonParser.Event.VALUE_STRING) {
                        nutriScoreGrade = parser.getValue().toString();
                        break;
                    }
                }
            }
        }
        
        if(nutriScoreGrade.equals("\0")) {
            return "Nutriscore grade could not be found"; 
        }
        if (nutriScoreGrade.startsWith("\"") && nutriScoreGrade.endsWith("\"")) {
            String noQuotesNutriScoreGrade = nutriScoreGrade.substring(1, nutriScoreGrade.length() - 1);
            return noQuotesNutriScoreGrade;
        }
        return nutriScoreGrade;
    }

}
